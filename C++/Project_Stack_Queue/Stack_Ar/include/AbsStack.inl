template < class Object >
AbsStack< Object >::AbsStack (size_t _size) : stackCapacity (_size)
{
	myStack = new Object [_size];
	stackSize = 0;
}

template < class Object >
void AbsStack< Object >::push ( const Object & _candidate)
{
	myStack[stackSize] = _candidate;
	stackSize++;	
}

template < class Object >
Object AbsStack< Object >::pop ( )
{
	stackSize--;
	return myStack[stackSize];
}

template < class Object >
Object AbsStack< Object >::top ( ) const
{
	return myStack[stackSize - 1];
}

template < class Object >
bool AbsStack< Object >::isEmpty ( ) const
{
	return (stackSize == 0);
}

template < class Object >
void AbsStack< Object >::makeEmpty ( )
{
	stackSize = 0;
}