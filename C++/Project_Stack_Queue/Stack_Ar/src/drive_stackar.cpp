#include "stackar.h"


int main ()
{
	StackAr<std::string> pantheon (5);
	
	if(pantheon.isEmpty())
		std::cout << "The stack is empty"<< std::endl;
	
	pantheon.push("Vishnu");
	std::cout << "The element at the top now is: " << pantheon.top() << std::endl;
	pantheon.push("Ananta");
	std::cout << "The element at the top now is: " << pantheon.top() << std::endl;
	
	pantheon.push("Shakti");
	pantheon.push("Apsaras");
	pantheon.push("Brahma");
	pantheon.push("Shiva");
	
	std::cout << "The element taken from the top is: " << pantheon.pop() << std::endl;
	std::cout << "The element taken from the top is: " << pantheon.pop() << std::endl;
	
	pantheon.makeEmpty();
	
	if(pantheon.isEmpty())
		std::cout << "The stack is empty"<< std::endl;

	return EXIT_SUCCESS;
}