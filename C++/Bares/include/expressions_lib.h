#include "header.h"
#include <string>

/* Classe que armazena e faz o tratamento das expressões passadas pelo arquivo de entrada.
 */

class Expression
{
	public:
		Expression( std::string _expression = "" ) :
			expression(_expression) 
		{ /*empty*/ }

		~Expression()
		{
			tokenized.makeEmpty();
			postfix.makeEmpty();
		}

		int char_type( char );

		void char_expected( int );

	private:
		std::string expression;
		Queue<int> tokenized;
		Queue<int> postfix;
		int err_column;
		int err_type;
};