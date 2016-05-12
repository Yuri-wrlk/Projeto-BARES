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
		Queue<std::string> pre_tokenized;
		Queue<std::string> tokenized;
		Queue<std::string> postfix;
		Stack<char> operatorStack;
		int err_column;
		int err_type;
		
		enum errors_types { OUT_OF_RANGE = 1, ILL_FORMED, INVALID_OPERAND, EXTRANEOUS, MISMATCH, LOST_OPERATOR, MISSING_CLOSING, ZERO_DIV, OVRFLOW };
		
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
			err_type(0)
		{ /*empty*/ }

		~Expression()
		{
			tokenized.makeEmpty();
			postfix.makeEmpty();
		}

		bool analysis( void );

		bool isExpression( size_t & start, size_t end );
		bool isTerm( size_t & index );
		bool isNumber( size_t & index );

		// bool pre_tokenize( void );

		bool tokenize( void );

		bool isOpBracket( char );

		bool isClBracket( char );

		bool isOperator( char );

		bool isInteger( char );

		std::string getError( void );

		/*
		bool analysis();		
		
		void parse();
		
		bool is_term ();
		
		bool is_expression();

		int char_type( char );

		void char_expected( int );
		*/
		

};


#include "expressions_lib.inl"
#endif