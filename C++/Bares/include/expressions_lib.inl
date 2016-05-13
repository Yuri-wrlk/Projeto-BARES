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
		if(expression[i] == ' ' or expression[i] == 9) //tab in ASCII is 9
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
			std::string msg;
			errorMessage( msg );
			std::cout << msg << std::endl;
			return false;
		}
		
		tokenized.enqueue(aux);
		aux = "";
		
		
	}
	
	if(!(bracket_count.isEmpty()))
	{
		err_type = MISSING_CLOSING;
		err_column = bracket_count.top() + 1;
		
		std::string msg;
		errorMessage( msg );
		std::cout << msg << std::endl;
		return false;
	}
	
	if(last_char == OPERATOR)
	{
		err_type = ILL_FORMED;
		err_column = i + 1;
		std::string msg;
		errorMessage( msg );
		std::cout << msg << std::endl;
		return false;
	}

	/*
	std::cout << "tokenized is\n";
	std::cout << tokenized;
	std::cout << "\n";
	*/
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

bool Expression::analysis(const std::string & value, int position)
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
		if( last_char == DEVOID or last_char == OPERATOR)
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
		
		if ( last_char == NUMBER or last_char == ')')
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
		
		if (last_char == '(')
		{
			err_type = ILL_FORMED;
			err_column = position + 1;
			return false;
		}
		if(isOperator(last_char))
		{
			err_type = EXTRANEOUS;
			err_column = position + 1;
			return false;
		}
		last_char = CL_PARENTHESIS;
	}
	
	else if(isLetter(value[0]))
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

void Expression::errorMessage( std::string & msg )
{
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
			msg = "Division by zero!: column " + std::to_string(err_column);
			break; 
		case OVRFLOW:
			msg = "Numeric overflow error!: column " + std::to_string(err_column);
			break;
	}
}