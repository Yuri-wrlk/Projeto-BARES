template < class Object >
void StackAr< Object >::push ( const Object & _candidate)
{
	if(AbsStack< Object >::stackSize ==  AbsStack< Object >::stackCapacity)
	{
		throw std::length_error("Capacity was exceeded! Trying to add an element to an already full stack");
		return;
	}
	AbsStack< Object >::myStack[AbsStack< Object >::stackSize] = _candidate;
	AbsStack< Object >::stackSize++;	
}

template < class Object >
Object StackAr< Object >::pop ( )
{
	if(AbsStack< Object >::stackSize < 1)
	{
		throw std::length_error("Trying to remove an element from an empty stack");
	}
	AbsStack< Object >::stackSize--;
	return AbsStack< Object >::myStack[AbsStack< Object >::stackSize];

}

template < class Object >
Object StackAr< Object >::top ( ) const
{
	if(AbsStack< Object >::stackSize < 1)
	{
		throw std::length_error ("There is no element at the top of the stack, it's empty");
	}
	return AbsStack< Object >::myStack[AbsStack< Object >::stackSize - 1];
}