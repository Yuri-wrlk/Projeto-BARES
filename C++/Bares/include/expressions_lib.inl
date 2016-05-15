#include "expressions_lib.h"

bool Expression::isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

bool Expression::tokenize( void )
{

	std::string aux = "";
	auto i (0u);
	for(; i < expression.length(); ++i)
	{
		// std::cout << ">>>Last char is " << last_char << "\n";
		if(expression[i] == 32 or expression[i] == 9) //tab in ASCII is 9
			continue;
		
		aux = aux + expression[i];
		
		if ( isdigit(expression[i]) ) 
		{
			while( isdigit(expression[i + 1]) and i + 1 < expression.length())
			{	
				aux = aux + expression[++i];
			}
		}
		
		
		if( !analysis(aux, i) )
		{
			return false;
		}
		
		tokenized.enqueue(aux);
		aux = "";
		
		
	}
	
	if(!(bracket_count.isEmpty()))
	{
		err_type = MISSING_CLOSING;
		err_column = bracket_count.top() + 1;
		return false;
	}
	
	if(last_char == OPERATOR)
	{
		err_type = ILL_FORMED;
		err_column = i + 1;
		return false;
	}

	return true;
}

bool Expression::isOperator(char candidate)
{
	for (int i = 0; i < 8; ++i)
	{
		if (candidate == operators[i])
			return true;
	}
	return false;
}

bool Expression::analysis( std::string & value, int position)
{
	if (isInteger(value))
	{
		if (last_char == NUMBER)
		{
			err_type = EXTRANEOUS;
			err_column = position + 1;
			return false;
		}
		
		char  *p;
		long int test = strtol(value.c_str(), &p, 10);
		
		if (test > 32767)
		{
			err_type = OUT_OF_RANGE;
			err_column = ( position - value.length() ) + 2;
			return false;
		}
		
		last_char = NUMBER;
		
	}
	
	else if( isOperator(value[0]) )
	{
		
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

		last_char = OPERATOR;
	}
	
	else if( value[0] == '(' )
	{
		bracket_count.push(position);
		
		if ( last_char == NUMBER or last_char == CL_PARENTHESIS)
		{
			err_type = EXTRANEOUS;
			err_column = position + 1;
			return false;
		}
		
		last_char = OP_PARENTHESIS;
		
	}
	
	else if( value[0] == ')' )
	{
		if (bracket_count.isEmpty())
		{
			err_type = MISMATCH;
			err_column = position + 1;
			return false;
		}
		
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

		last_char = CL_PARENTHESIS;
	}
	
	else if( isLetter(value[0]) )
	{
		err_type = ILL_FORMED;
		err_column = position + 1;
		return false;
	}
	
	else
	{
		err_type = INVALID_OPERAND;
		err_column = position + 1;
		return false;
	}
	
	return true;
}

bool Expression::isLetter(char candidate)
{
	if ( (candidate >= 65 and candidate <= 90) or (candidate >= 97 and candidate <= 122))
		return true;
		
	return false;
}

std::string Expression::errorMessage(  )
{
	std::string msg;
	
	switch(err_type)
	{
		case OUT_OF_RANGE:
			msg = "Numeric constant out of range: column " + std::to_string(err_column);
			break;
		case ILL_FORMED:
			msg = "Ill-formed expression or missing term detected: column " + std::to_string(err_column);
			break; 
		case INVALID_OPERAND:
			msg = "Invalid operand: column " + std::to_string(err_column);
			break; 
		case EXTRANEOUS:
			msg = "Extraneous symbol: column " + std::to_string(err_column);
			break; 
		case MISMATCH:
			msg = "Mismatch ’)’: column " + std::to_string(err_column);
			break; 
		case LOST_OPERATOR:
			msg = "Lost operator: column " + std::to_string(err_column);
			break; 
		case MISSING_CLOSING:
			msg = "Missing closing ’)’ to match opening ’(’ at: column " + std::to_string(err_column);
			break;
		case ZERO_DIV:
			msg = "Division by zero!";
			break; 
		case OVRFLOW:
			msg = "Numeric overflow error!";
			break;
	}
	return msg;
}

void Expression::infixToPostFix ()
{

	std::cout << "A fila infixa é:";
	std::cout << tokenized;
	
	std::string aux;
	std::string aux2;
	while(!tokenized.isEmpty())
	{
		aux = tokenized.dequeue();
		if(isInteger(aux))
		{
			postfix.enqueue(aux);
		}
		else
		{
			if(aux[0] == '(')
				operatorStack.push(aux[0]);
			else if (aux[0] == ')')
			{
				while(operatorStack.top() != '(')
				{
					aux2 = operatorStack.pop();
					postfix.enqueue(aux2);
				}
					
				
				operatorStack.pop();
			}
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
	
	while (!operatorStack.isEmpty())
	{
		aux2 = operatorStack.pop();
		postfix.enqueue(aux2);
	}
	
	std::cout << "A fila posfixa é:";
	std::cout << postfix;
}

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

bool Expression::calculate()
{
	infixToPostFix();
	Stack<int> operationStack;
	std::string aux;
	int operandA;
	int operandB;
	int result;

	while(!postfix.isEmpty())
	{
		aux = postfix.dequeue();
		if(isInteger(aux))
		{
			operationStack.push(std::stoi(aux));
		}
		else if (aux[0] == '@')
		{
			result = operationStack.pop();
			result *= -1;
			operationStack.push(result);
		}
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
			operationStack.push(result);
		}
	}
	
	expression_result = operationStack.pop();
	
	return true;
}

int Expression::getResult()
{
	return expression_result;
}