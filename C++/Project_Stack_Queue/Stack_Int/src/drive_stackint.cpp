#include "stackint.h"


int main ()
{
	StackInt mapa(2);
	
	if(mapa.isEmpty())
		std::cout << "A pilha está vazia"<< std::endl;
	
	mapa.push(4);
	std::cout << "O elemento do topo é: " << mapa.top() << std::endl;
	mapa.push(13);
	std::cout << "O elemento do topo é: " << mapa.top() << std::endl;
	
	mapa.push(78);
	mapa.push(162);
	mapa.push(907);
	mapa.push(456);
	
	std::cout << "O elemento retirado do topo é: " << mapa.pop() << std::endl;
	std::cout << "O elemento retirado do topo é: " << mapa.pop() << std::endl;
	
	mapa.makeEmpty();
	
	if(mapa.isEmpty())
		std::cout << "A pilha está vazia"<< std::endl;

	return EXIT_SUCCESS;
}