#include <stdexcept>
#include "stack.h"

template < typename Object >
Stack<Object>::Stack( int _size ) : 
	topo( 0 ),
	capacity( _size )
{
	myStack = new Object[ _size ];
}

template < typename Object >
void Stack<Object>::resize( int newLength )
{
	Object *P = new Object[ newLength ];

	for (int i = 0; i <= topo; ++i)
		P[i] = myStack[i];

	delete [] myStack;

	myStack = P;

	capacity = newLength;	
}

template < typename Object >
bool Stack<Object>::isEmpty() const
{
	return (topo == 0);
}

template < typename Object >
void Stack<Object>::makeEmpty()
{
	topo = 0;
}

template < typename Object >
void Stack<Object>::push( const Object & x )
{
	if ( topo == capacity )
		resize( 2 * capacity );

	myStack[ topo++ ] = x;
}

template < typename Object >
Object Stack<Object>::pop()
{
	if ( isEmpty() )
		throw std::length_error("Underflow!");

	return myStack[--topo];
}

template < typename Object >
Object Stack<Object>::top()
{
	return myStack[topo - 1];
}