#include "stackint.h"

StackInt::StackInt(size_t _size) : 
	stackCapacity (_size)
{
	myStack = new int [_size];
	stackSize = 0;
}

void StackInt::push ( const int & _candidate )
{
	if(stackSize ==  stackCapacity)
		resize();
	myStack[stackSize] = _candidate;
	stackSize++;
}

int StackInt::pop ( )
{
	if(stackSize > 0) 
	{
		stackSize--;
		return myStack[stackSize];
	}
	throw std::length_error ("Impossível remover elementos de uma pilha vazia!");
	return -1;

}

int StackInt::top ( ) const
{
	return myStack[stackSize - 1];
}

bool StackInt::isEmpty ( ) const
{
	return (stackSize == 0);
}

void StackInt::makeEmpty ( )
{
	stackSize = 0;
}

void StackInt::resize ()
{
	size_t _newSize = 2 * stackSize;
	int * _newArr =  new int [_newSize];

	memcpy(_newArr, myStack, sizeof(int) * stackSize);

	stackSize = _newSize;
	delete[] myStack;
	myStack = _newArr;
}