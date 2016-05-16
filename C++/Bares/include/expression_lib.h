/*!
 *	@file expression_lib.h
 *
 *  File with the Expression class header.
 */

#include "header.h"
#include <string>

#ifndef _EXP_
#define _EXP_

/*!
 *	@brief Expression class.
 *	
 *	Class that represents a single expression.
 */
class Expression
{
	private:

		//==================== ATTRIBUTES ====================


		// String containing the expression line read via input file.
		std::string expression;
		// Queue containing expression after tokenization.
		Queue<std::string> tokenized;
		// Queue containing expression in postfix format.
		Queue<std::string> postfix;
		// Stack used to calculate the expression result.
		Stack<char> operatorStack;
		// Indicates the column of a possible error on the expression.
		int err_column;
		// Indicates the type a possible error on the expression.
		int err_type;
		// Result value of the expression after calculation.
		int expression_result;
		// Indicates the column of each opening parenthesis on the expression. Used for error detection purposes.
		Stack<int> bracket_count;

		
		// Possible types of characteres that can appear on the expression.
		// DEVOID indicates the starting of the expression. It is used on the tokenize() method.
		enum char_types { NUMBER, OPERATOR, OP_PARENTHESIS, CL_PARENTHESIS, DEVOID};

		// Error types the program supports.		
		enum error_types { 	OUT_OF_RANGE = 1, ILL_FORMED = 2, INVALID_OPERAND = 3,
							EXTRANEOUS = 4, MISMATCH = 5, LOST_OPERATOR = 6, 
							MISSING_CLOSING = 7, ZERO_DIV = 8, OVRFLOW = 9};

		// Indicates the type of the last character read. It is used on the analysis() method.
		char_types last_char;
		
		// Operators accepted by the program. '@' represents unary minus.
		char operators [7] = {  '+', '-', '%', '*', '/', '^', '@' };

		//==================== PRIVATE METHODS ====================

		// For detailed description of each method, see 'include/expression_lib.inl' file.

		// Checks if the content of a string is an integer number.
		bool isInteger( const std::string & );

		// Checks if a given char is a valid operator.
		bool isOperator( char );

		// Checks if some given char is a letter. Used for error detection purposes.		
		bool isLetter( char );

		// Analyzes the current character read in search of errors. Used during tokenization.
		bool analysis( std::string &, int );
		
		// Converts a infix expression to its postfix form.
		void infixToPostFix ( void );
		
		// Gets the precedence of an operator.
		int getPrecedence( char );


	public:
		/*!
		 *	@brief Class constructor.
		 *	@param _expression A expression read from file.
		 *
		 *	The class constructor sets the expression as the string given as argument, being empty by default.
		 *	The err_column and err_type variables are set to 0.
		 *	The last_char variable is set as DEVOID, indicating the beginning of the expression. 
		 */
		Expression( std::string _expression = "" ) :
			expression(_expression),
			err_column(0),
			err_type(0),
			last_char(DEVOID)
		{ /*empty*/ }

		/*!
		 *	@brief Class destructor.
		 *
		 *	Empties all queues and stacks.
		 */
		~Expression()
		{
			tokenized.makeEmpty();
			postfix.makeEmpty();
			operatorStack.makeEmpty();
			bracket_count.makeEmpty();
		}

		//==================== PUBLIC METHODS ====================

		// For detailed description of each method, see 'include/expression_lib.inl' file.

		//sud Tokenizes the expression.
		bool tokenize( void );

		// Gets the error message, in case the expression contains error.
		std::string errorMessage( void );
		
		// Calculates the expression result.
		bool calculate( void );
		
		// Gets the expression result.
		int getResult( void );
		
};


#include "expression_lib.inl"
#endif