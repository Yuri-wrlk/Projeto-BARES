#include "header.h"
#include <string>

/* Classe que armazena e faz o tratamento das expressões passadas pelo arquivo de entrada.
 */
#ifndef _EXP_
#define _EXP_


class Expression
{
	private:
		std::string expression;
		Queue<std::string> tokenized;
		Queue<std::string> postfix;
		Stack<char> operatorStack;
		int err_column;
		int err_type;
		Stack<int> bracket_count;
		
		enum char_types { NUMBER, OPERATOR, OP_PARENTHESIS, CL_PARENTHESIS, DEVOID};
		
		enum error_types { OUT_OF_RANGE = 1, ILL_FORMED, INVALID_OPERAND, EXTRANEOUS, MISMATCH, LOST_OPERATOR, MISSING_CLOSING, ZERO_DIV, OVRFLOW };
		
		char_types last_char;
		
		/*
		enum characters { 	PLUS = 1, SIMPLE_MINUS = 1, TIMES = 2, DIV = 2, MOD = 2, 
							EXP = 3, UNARY_MINUS = 4, OP_PARENTHESIS = 5, CL_PARENTHESIS = 5, 
							NUMBER = 6,  NON_SUPPORTED = 7	};
		*/

		char operators [6] = {  '+', '-', '%', '*', '/', '^' }; 

	public:
		Expression( std::string _expression = "" ) :
			expression(_expression),
			err_column(0),
			err_type(0),
			last_char(DEVOID)
		{ /*empty*/ }

		~Expression()
		{
			tokenized.makeEmpty();
			postfix.makeEmpty();
		}

		bool analysis(const std::string &, int );
		
		bool tokenize( void );
		
		bool isInteger(const std::string & );

		bool isOperator(char);
		
		bool isLetter(char);
		
};


#include "expressions_lib.inl"
#endif