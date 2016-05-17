/*!
 *	@file expression_lib.inl
 *
 *  File with the Expression class methods implementation.
 */

#include "expression_lib.h"


/*!
 *	@brief Tests if a string is an integer
 *	@param s A token string that contains a value
 * 	@return True if the value is an integer, False if not
 *
 *	This is a slightly modified function of someone else's authorship.
 *	Extracted from: http://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int.
 */
bool Expression::isInteger(const std::string & s)
{
	// Check if s is empty or if it's first element is a number
   	if(s.empty() || ((!isdigit(s[0])) && (isOperator(s[0]) ) ) ) return false ;

   	char * p ;
   	strtol(s.c_str(), &p, 10) ;

   	return (*p == 0) ;
}

/*!
 *	@brief Tokenizes the line gotten from the file, sending each element to parsing.
 * 	@return True if no error was found at any moment, false otherwise
 *
 *	The expression string, declared in Expression class, is examined sequentially
 *	ignoring any spaces.
 *	Then each item is sent to the analysis function to check whether there is any 
 *	error, if none is found, the item is inserted at the end of tokenized queue 
 *	(also declared in Expression class). At last, a few other possible errors are
 *	analyzed at the end of tokenization.
 *
 */
bool Expression::tokenize( void )
{
	// Auxiliar string that will receive possible tokens
	std::string aux = "";
	// Simple counter for the loop
	auto i (0u);	
	// Runs through the entire length of expression
	for(; i < expression.length(); ++i)  
	{
		//tab in ASCII is 9, space is 32
		if(expression[i] == 32 or expression[i] == 9) 	
			continue;									
		
		// aux gets the possible character
		aux = aux + expression[i];
		
		// If the gotten character is a digit, get the rest of the number
		if ( isdigit(expression[i]) ) 
		{
			while( isdigit(expression[i + 1]) and i + 1 < expression.length())
			{	
				aux = aux + expression[++i];
			}
		}
		
		/* The item is then sent to the analysis function, if an error is found
		 * the method stops immediately, returning false
		 */
		if( !analysis(aux, i) )
		{
			return false;
		}
		
		// If no problem was found, it is inserted in the tokenized queue		
		tokenized.enqueue(aux);
		// Then aux is reset
		aux = "";
		
		
	}
	
	/* After the string is fully tokenized, it is checked whether there is any
	 * parenthesis left open, if there is any, the top on bracket_count stack shows
	 * us where is it's position.
	 */
	if(!(bracket_count.isEmpty()))
	{
		err_type = MISSING_CLOSING;
		err_column = bracket_count.top() + 1;
		return false;
	}
	
	/* Another error may occur when the last item found is an operand, this means
	 * that the formula lacks an operand, therefore it's ill-formed
	 */
	if(last_char == OPERATOR)
	{
		err_type = ILL_FORMED;
		err_column = i + 1;
		return false;
	}

	return true;
}

/*!
 *	@brief Tests if a character is a valid operator
 *	@param candidate The character to be tested
 * 	@return True if the value is an valid operator, False if not
 *
 *	Compares if candidate is an operator between  '+', '-', '%', '*', '/', '^' or
 *  '@' (@ stands for unary minus).
 */
bool Expression::isOperator( char candidate )
{
	/* Runs through the string that contais possible operators, comparing to all 
	 * of them, if a match is found, then candidate is viable
	 */ 
	for (int i = 0; i < 8; ++i)
	{
		if (candidate == operators[i])
			return true;
	}
	return false;
}

/*!
 *	@brief Analyzes a character on the expression looking for errors.
 * 	@param value The character to be analyzed.
 *	@param position The character's column on the expression.
 * 	@return True if no error is identified, false otherwise.
 * 
 *  The method gets the character passed as parameter and checks if it represents 
 * 	any error on the expression. To do so, it considers the current character type
 * 	and the type of the last character read on the expression. The last character
 * 	type indicates which type is expected on the current character. In case an error
 *	is identified, the method sets the attributes 'err_type' accordingly with the 
 *	error and 'err_column' with the position passed as argument (adjusted to show real 
 * 	column), and returns false.
 *	If no error is identified, the method returns true.
 *
 *	The basics of a well-formed expression are:
 *	- A number must be succeeded by an operator or a closing parenthesis.
 *	- An operator must be succeeded by a number or an opening parenthesis.
 *	- An opening parenthesis must be succeeded by a number or an opening parenthesis.
 * 	- A closing parenthesis must be succeeded by an operator or a closing parenthesis.
 *
 */
bool Expression::analysis( std::string & value, int position )
{
	/* If the current character is a number, errors occur when last character is:
	 * - A number.
	 * - A closing parenthesis.
	 */
	if (isInteger(value))
	{
		if ( last_char == NUMBER or last_char == CL_PARENTHESIS )
		{
			err_type = EXTRANEOUS;
			err_column = position + 1;
			return false;
		}
		
		char  *p;
		long int test = strtol(value.c_str(), &p, 10);
		
		// There's also the possibility of the number being out of range.
		if (test > 32767)
		{
			err_type = OUT_OF_RANGE;
			// The error column is adapted to point the error to the position of the number's first digit.
			err_column = ( position - value.length() ) + 2;
			return false;
		}
		
		// If no error is catch, last_char is updated.
		last_char = NUMBER;
		
	}
	
	/* If the current character is an operator, errors occur when last character is:
	 * - An operator.
	 * - An opening parenthesis.
	 * 
	 * Also, an expression shall not be initiated by an operator. The starting of
	 * an expression is identified by the DEVOID state.
	 */
	else if( isOperator(value[0]) )
	{
		/* There is the especial case of the minus operator. It can be a binary operator,
		 * expecting two operands, or an unary operator, expecting a single number.
		 * This last case will happen in the starting of the expression or when the last
		 * character read is an operator or an opening parenthesis.
		 */
		if ( value[0] == '-' )
		{
			if ( last_char == OPERATOR or last_char == OP_PARENTHESIS or last_char == DEVOID )
			{
				value = "@";
			}
		}
		else if( last_char == DEVOID or last_char == OPERATOR)
		{
			err_type = LOST_OPERATOR;
			err_column = position + 1;
			return false;
		}
		else if (last_char == OP_PARENTHESIS)
		{
			err_type = ILL_FORMED;
			err_column = position + 1;
			return false;
		}
		
		// If no error is catch, last_char is updated.
		last_char = OPERATOR;
	}
	
	/* If the current character is an opening parenthesis, errors occur when last character is:
	 * - A number.
	 * - A closing parenthesis.
	 */
	else if( value[0] == '(' )
	{
		// The column of the bracket is pushed into the bracket_count stack.
		bracket_count.push(position);
		
		if ( last_char == NUMBER or last_char == CL_PARENTHESIS)
		{
			err_type = EXTRANEOUS;
			err_column = position + 1;
			return false;
		}
		
		// If no error is catch, last_char is updated.
		last_char = OP_PARENTHESIS;
		
	}
	
	/* If the current character is a closing parenthesis, errors occur when last character is:
	 * - An operator.
	 * - An opening parenthesis.
	 * 
	 * Also, an expression shall not be initiated by a closing parenthesis.
	 */
	else if( value[0] == ')' )
	{
		/* The bracket_count stack is checked to see if a parenthesis has been opened
		 * somewhere in the expression. In case the stack is empty, meaning no 
		 * parenthesis have been opened yet, a mismatch parenthesis error occurs.
		 */
		if ( bracket_count.isEmpty() )
		{
			err_type = MISMATCH;
			err_column = position + 1;
			return false;
		}
		
		// If a closing parenthesis is found, an opening parenthesis must be popped from the stack.
		bracket_count.pop();
		
		if ( last_char == OP_PARENTHESIS )
		{
			err_type = ILL_FORMED;
			err_column = position + 1;
			return false;
		}

		if( last_char == OPERATOR )
		{
			err_type = EXTRANEOUS;
			err_column = position + 1;
			return false;
		}
		
		// If no error is catch, last_char is updated.
		last_char = CL_PARENTHESIS;
	}
	
	// No letter from the latin alphabet are allowed in well-formed expressions.
	else if( isLetter(value[0]) )
	{
		err_type = ILL_FORMED;
		err_column = position + 1;
		return false;
	}
	
	// If the character happens to be any other symbol, it is an invalid operand.
	else
	{
		err_type = INVALID_OPERAND;
		err_column = position + 1;
		return false;
	}
	
	return true;
}

/*!
 *	@brief Tests if a character is a character in the classic latin alphabet. 
 *	@param candidate The character to be tested.
 * 	@return True if the value is inside the letter range in the ASCII table, False if not.
 *
 *	Compares if candidate is a simple or a capital character.
 */
bool Expression::isLetter( char candidate )
{
	if ( (candidate >= 65 and candidate <= 90) or (candidate >= 97 and candidate <= 122))
		return true;
		
	return false;
}


/*!
 *	@brief Returns a string with the error, if there is any.
 * 	@return msg A string containing any error found in the expression.
 *
 *	This method analyzes the error that is set inside the err_type variable, then
 *	sets a string with the error type and the column in which it occurred.
 */
std::string Expression::errorMessage( void )
{
	std::string msg;
	
	switch(err_type)
	{
		case OUT_OF_RANGE:
			msg = "E1 " + std::to_string(err_column);
			break;
		case ILL_FORMED:
			msg = "E2 " + std::to_string(err_column);
			break; 
		case INVALID_OPERAND:
			msg = "E3 " + std::to_string(err_column);
			break; 
		case EXTRANEOUS:
			msg = "E4 " + std::to_string(err_column);
			break; 
		case MISMATCH:
			msg = "E5 " + std::to_string(err_column);
			break; 
		case LOST_OPERATOR:
			msg = "E6 " + std::to_string(err_column);
			break; 
		case MISSING_CLOSING:
			msg = "E7 " + std::to_string(err_column);
			break;
		case ZERO_DIV:
			msg = "E8";
			break; 
		case OVRFLOW:
			msg = "E9";
			break;
		default:
			msg = "No error found";
			break;
	}
	return msg;
}

/*!
 *	@brief Converts expression from infix to postfix format.
 *
 *	The method converts the tokenized expression, in the infix format, to the
 *	postfix notation. The tokens are read one by one. When the token is a number, 
 * 	it is directly sent to the postfix queue. When it is an operator, it is sent
 *	to the operator stack, only being sent to the postfix queue when another 	
 * 	operator with lower precedence enters the queue or at the end of the process.
 */
void Expression::infixToPostFix ( void )
{
	// Receives the token temporarily
	std::string aux;
	// Does the same as aux, only used in some cases
	std::string aux2;
	while(!tokenized.isEmpty())
	{
		aux = tokenized.dequeue();
		
		// If it's a integer it is put directly in the queue
		if(isInteger(aux))
		{
			postfix.enqueue(aux);
		}
		else
		{	
			/* If it's a opening parenthesis it's put directly into the operator	
			 * stack, it has gotten the lowest precedence possible, but does not
			 * generate any conflict
			 */
			if(aux[0] == '(')
				operatorStack.push(aux[0]);
			/* If it's a closing parenthesis, it means we've reached the end of 
			 * the expression that beginned at the last opening parenthesis, so
			 * we remove all operators from the stack and put them at the postfix
			 * queue, lastly we remove the corresponding opening parenthesis
			 */
			else if (aux[0] == ')')
			{
				while(operatorStack.top() != '(')
				{
					aux2 = operatorStack.pop();
					postfix.enqueue(aux2);
				}
					
				
				operatorStack.pop();
			}
			/* If it's neither an integer nor a parenthesis, we should have an 
			 * operator, so we should check it's priority whether it's priority
			 * greater than the last operator (in this case we simply insert it)
			 * or we keep removing operators and queueing them until we find an 
			 * operator with lower precedence
			 */
			else 
			{
				while(!operatorStack.isEmpty() and getPrecedence(aux[0]) <= getPrecedence(operatorStack.top()))
				{
					aux2 = operatorStack.pop();
					postfix.enqueue(aux2);
				}
					
				operatorStack.push(aux[0]);
			}
		}
	}
	
	// After the expression is fully read, we enqueue the remaining operators
	while (!operatorStack.isEmpty())
	{
		aux2 = operatorStack.pop();
		postfix.enqueue(aux2);
	}
}

/*!
 *	@brief Gets the precedence of an operator.
 *	@param op The operator we want to know the precedence.
 *	@return The precedence of the operator.
 *	
 *	Gets the precedence of the operator passed as parameter, accordingly with the following:
 *	() 		= precedence 0,
 *	+, - 	= precedence 1,
 *	*, /, % = precedence 2,
 *	^ 		= precedence 3,
 *	@ 		= precedence 4.
 *
 *	The '@' is used for unary minus.
 *	
 */
int Expression::getPrecedence( char op )
{
	
	if( op == '+' or op == '-' )
		return 1;
	else if ( op == '*' or op == '/' or op == '%' )
		return 2;
	else if ( op == '^' )
		return 3;
	else if (op == '@')
		return 4;
	else
		return 0;
}


/*!
 *	@brief Calculates the expression result.
 *	@return True if the calculation was successful, false if an error occurred.
 *
 *	This method calculates the resulting value from the expression. First, it
 *	calls the infixToPostFix() method to convert the expression format. Then, it
 *	uses an auxiliary stack to store the operands and perfom the operations in 
 *	the order stablished by the postfix notation. By the end of all operations, 
 *	the result remains on the auxiliary stack and the 'expression_result' 
 *	attribute receives this value.
 *
 */
bool Expression::calculate( void )
{
	infixToPostFix();
	// Auxiliary stack to put the operands.
	Stack<int> operationStack;
	// String variable to get each expression token.
	std::string aux;
	int operandA;
	int operandB;
	int result;
	
	while(!postfix.isEmpty())
	{	
		// Dequeues a token and pass it to the aux variable.
		aux = postfix.dequeue();
		// If the token is a number, it is added directly to the stack.
		if(isInteger(aux))
		{
			operationStack.push(std::stoi(aux));
		}
		/* If the token is an unary minus, the top element is popped from the 
		 * operands stack, multiplied by -1 and pushed back into the stack.
		 */
		else if (aux[0] == '@')
		{
			result = operationStack.pop();
			result *= -1;
			operationStack.push(result);
		}
		/* If the token is an operator, the two operands are popped from the stack
		 * and the corresponding operation is executed with them. A test is performed
		 * on operations that can produce some sort of error, which are:
		 * - Overflow, produced by +, -, * and ^ operators.
		 * - Division by 0, produced by / operator.
		 */
		else
		{
			operandB = operationStack.pop();
			operandA = operationStack.pop();
			
			if (aux[0] == '+')
			{
				result = operandA + operandB;	
				if ( result > 32767 or result < -32767 )
				{
					err_type = OVRFLOW;
					return false;
				}
					
			}
			else if (aux[0] == '-')
			{
				result = operandA - operandB;	
				if (result > 32767 or result < -32767 )
				{
					err_type = OVRFLOW;
					return false;
				}
			}
			else if (aux[0] == '*')
			{
				result = operandA * operandB;
				if ( result > 32767 or result < -32767 )
				{
					err_type = OVRFLOW;
					return false;
				}
			}
			else if (aux[0] == '/')
			{
				if ( operandB == 0 )
				{
					err_type = ZERO_DIV;
					return false;
				}
				result = operandA / operandB;
			}
			else if (aux[0] == '%')
			{
				result = operandA % operandB;
			}
			else if (aux[0] == '^')
			{
				result = pow(operandA, operandB);
				if ( result > 32767 or result < -32767  )
				{
					err_type = OVRFLOW;
					return false;
				}
			}
			/* The result of the current operation is pushed into the stack, to be used
			 * in another operation or to represent the final result.
			 */
			operationStack.push(result);
		}
	}
	
	// After all operations, the expression result should be the only element in the stack.
	expression_result = operationStack.pop();
	
	return true;
}

/*!
 *	@brief Gets the result of the expression.
 * 	@return The expression result as an integer.
 *
 *  Gets the result of the expression and returns it as an integer.
 */
int Expression::getResult( void )
{
	return expression_result;
}