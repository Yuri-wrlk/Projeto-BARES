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
		int expression_result;
		Stack<int> bracket_count;
		
		enum char_types { NUMBER, OPERATOR, OP_PARENTHESIS, CL_PARENTHESIS, DEVOID};
		
		enum error_types { OUT_OF_RANGE = 1, ILL_FORMED, INVALID_OPERAND, EXTRANEOUS, MISMATCH, LOST_OPERATOR, MISSING_CLOSING, ZERO_DIV, OVRFLOW };

		char_types last_char;
		
		char operators [7] = {  '+', '-', '%', '*', '/', '^', '@' }; 


				
		bool isInteger(const std::string & );

		bool isOperator(char);
		
		bool isLetter(char);
		
		bool analysis(std::string &, int );
		
		void infixToPostFix ();
		
		int getPrecedence( char );


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
			operatorStack.makeEmpty();
			bracket_count.makeEmpty();
		}

		bool tokenize( void );

		std::string errorMessage( );
		
		bool calculate();
		
		int getResult();
		
};


#include "expressions_lib.inl"
#endif