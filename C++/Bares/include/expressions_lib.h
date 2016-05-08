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
		int last_type;
		Stack<char> operatorStack;
		int err_column;
		int err_type;
		
		enum errors_types {OUT_OF_RANGE, ILL_FORMED, INVALID_OPERAND, EXTRANEOUS, MISMATCH, LOST_OPERATOR, MISSING_CLOSING, ZERO_DIV, OVERFLOW};
		
		enum characters { 	PLUS = 1, SIMPLE_MINUS = 1, TIMES = 2, DIV = 2, MOD = 2, 
							EXP = 3, UNARY_MINUS = 4, OP_PARENTHESIS = 5, CL_PARENTHESIS = 5, 
							NUMBER = 6,  NON_SUPPORTED = 7	}

	public:
		Expression( std::string _expression = "" ) :
			expression(_expression) 
		{ /*empty*/ }

		~Expression()
		{
			tokenized.makeEmpty();
			postfix.makeEmpty();
		}
		
		
		void parse();
		
		bool is_term ();
		
		bool is_expression();
		
		void tokenize ();

		int char_type( char );

		void char_expected( int );
		
		

};


#include "expressions_lib.inl"
#endif