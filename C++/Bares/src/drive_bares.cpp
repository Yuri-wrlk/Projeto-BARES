#include "queue.h"
#include "stack.h"

int main ()
{


	Queue<double> random;
	Stack<double> random2;

	Queue<double> mapa(3);
	std::cout << "Is Paul joining?" << std::endl;
	mapa.enqueue(1.3);
	std::cout << "Aparently yes\n" << std::endl;

	std::cout << mapa << std::endl;

	mapa.dequeue();

	std::cout << "Is George joining?" << std::endl;
	mapa.enqueue(4.6);
	std::cout << "Aparently yes\n" << std::endl;

	std::cout << mapa << std::endl;

	std::cout << "Is John joining?" << std::endl;
	mapa.enqueue(7.89);
	std::cout << "Aparently yes\n" << std::endl;

	std::cout << mapa << std::endl;

	std::cout << "Is Ringo joining?" << std::endl;
	mapa.enqueue(9.37);
	std::cout << "Aparently yes\n" << std::endl;
	
	std::cout << mapa << std::endl;

	std::cout << "Is Yoko joining?" << std::endl;
	mapa.enqueue(14.52);
	std::cout << "Aparently yes\n" << std::endl;

	std::cout << mapa << std::endl;

	std::cout << mapa.getFront() << std:: endl;

	Stack<int> my_stack(2);

	if( my_stack.isEmpty() )
		std::cout << "Pilha vazia!\n\n";
	
	std::cout << "my_stack: \n" << my_stack;

	my_stack.push(8);
	my_stack.push(16);
	my_stack.push(32);
	my_stack.push(64);
	my_stack.push(128);


	std::cout << "my_stack depois de pushs: \n" << my_stack;

	std::cout << "Elemento do topo: " << my_stack.top() << "\n\n";

	std::cout << "Retirando elemento " << my_stack.pop() << " do topo da pilha.\n";
	std::cout << "Retirando elemento " << my_stack.pop() << " do topo da pilha.\n";

	std::cout << "my_stack depois de 2 pops: \n" << my_stack;
	std::cout << "Elemento do topo: " << my_stack.top() << "\n\n";

	my_stack.push(256);
	my_stack.push(512);
	my_stack.push(1024);
	my_stack.push(2048);
	my_stack.push(4096);
	my_stack.push(8192);

	std::cout << "my_stack depois de pushs: \n" << my_stack;
	std::cout << "Elemento do topo: " << my_stack.top() << "\n\n";

	std::cout << "Retirando elemento " << my_stack.pop() << " do topo da pilha.\n";
	std::cout << "Retirando elemento " << my_stack.pop() << " do topo da pilha.\n";
	std::cout << "Retirando elemento " << my_stack.pop() << " do topo da pilha.\n";
	std::cout << "Retirando elemento " << my_stack.pop() << " do topo da pilha.\n";

	std::cout << "my_stack depois de 4 pops: \n" << my_stack;
	std::cout << "Elemento do topo: " << my_stack.top() << "\n\n";

	my_stack.makeEmpty();
	std::cout << "my_stack depois de makeEmpty: \n" << my_stack;

	if( my_stack.isEmpty() )
		std::cout << "Pilha agora está vazia!\n";


	return EXIT_SUCCESS;
}