#include "expressions_lib.h"

bool Expression::analysis( void )
{
	int previous = 0;

	bool first_char = true;

	int bracket_count = 0;

	for (size_t i = 0; i < expression.length() - 1; ++i)
	{
		
		while(expression[i] == 32 or expression[i] == 9)
			continue;

		if ( first_char )
		{
			if( isOperator(expression[i]) )
			{
				err_type = ILL_FORMED;
				err_column = i;
				return false;
			}
			else if ( isClBracket(expression[i]) )
			{
				err_type = MISMATCH;
				err_column = i;
				return false;
			}
			else
			{
				first_char = false;
				if (/* condition */)
				{
					/* code */
				}
				continue;
			}
		}
		else
		{
			if ( isInteger(expression[i]) )
			{
				if ( isInteger(expression[i+1]) )
				{
					continue;
				}
				else 
			}

		}
		return true;
	}

}

bool isExpression( size_t & start, size_t end )
{
	if ( isTerm(start) )
	{
		while( start < end )
		{
			if ( isOperator(start) )
			{
				start++;
				if ( isTerm(start) )
				{
					continue;
				}
				else
				{
					err_type = LOST_OPERATOR;
					err_column = i+1;
				}
			}
			else
			{
				err_type = INVALID;
				err_column = i+1;

			}
		}
	}
	else
	{
		err_type = EXTRANEOUS;
		err_column = i+1;
	}
	return true;


}

bool isTerm( size_t & index )
{
	if ( isNumber(index)  )
	{
		index++;
		return true;
	}

	else if (expression[index] == '+' or expression[index] == '-')
	{
		while( expression[index+1] == '+' or expression[index+1] == '-')
			index++;

		if (isNumber(index))
		{
			index++;
			return true;
		}
		else
		{
			err_type = ILL_FORMED;
			err_column = i+1;
			return false;
		}
	}

	// =============== FINISH THIS! ==================
	else if( isOpBracket(expression[index]) )
	{


	}
	// ===============================================
}

bool isNumber( size_t & index )
{
	if (expression[index] > 47 && expression[index] < 58)
	{
		while( expression[index + 1] > 47 && expression[index + 1] < 58 )
			i++;
		
		return true;
	}
	return false;	
}
/*
bool Expression::pre_tokenize( void )
{

	std::string aux = "";
	
	for(auto i (0u); i < expression.length(); ++i)
	{
		aux = aux + expression[i];

		if (isInteger(expression[i])) 
		{
			while(i + 1 < expression.length() && isInteger(expression[i + 1]))
			{	
				aux = aux + expression[++i];
			}

		}

		pre_tokenized.enqueue(aux);
		aux = "";
	}

	std::cout << "tokenized is\n";
	std::cout << pre_tokenized;
	std::cout << "\n";
	return true;
}
*/

inline bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

bool Expression::tokenize( void )
{

	std::string aux = "";
	
	for(auto i (0u); i < expression.length(); ++i)
	{
		if(expression[i] == ' ')
			continue;
		else if ( isOperator(expression[i]) )
		{
			aux = aux + expression[i];
			tokenized.enqueue( aux );
			aux = "";
		}
		else if (isInteger(expression[i])) 
		{
			aux = aux + expression[i];
			while(i + 1 < expression.length() && isInteger(expression[i + 1]))
			{	
				aux = aux + expression[++i];
			}

			tokenized.enqueue(aux);
			aux = "";
		}
	}

	std::cout << "tokenized is\n";
	std::cout << tokenized;
	std::cout << "\n";
	return true;
}
	
bool Expression::isOperator( char candidate )
{
	for (int i = 0; i < 6; ++i)
	{
		if (candidate == operators[i])
			return true;
	}
	return false;
}

bool Expression::isOpBracket( char candidate )
{
	return (candidate == '(');
}

bool Expression::isClBracket( char candidate )
{
	return (candidate == ')');
}

bool Expression::isInteger( char candidate )
{
	if (candidate > 47 && candidate < 58)
		return true;
	return false;
}

std::string Expression::getError( void )
{
	std::string error_msg;
	error_msg = "E" + std::to_string(err_type) + " " + std::to_string(err_column);
	return error_msg;
}