#include <iostream>
#include <algorithm>
#include <cstring>
#include <stdexcept>

#ifndef _ABS_STACK_
#define _ABS_STACK_

template < class Object >
class AbsStack 
{
	public:
		AbsStack (size_t );
		//Default constructor

		virtual ~ AbsStack () { /* Empty */ } // Default destructor

		// Basic members
		virtual void push ( const Object & );
		virtual Object pop ( );
		virtual Object top ( ) const;
		bool isEmpty ( ) const ;
		void makeEmpty ( );
	
	private:
		// Disable copy constructor
		AbsStack ( const AbsStack & ) { /* Empty */ }

	protected:
		// Class variables
		Object * myStack;
		size_t stackSize;
		size_t stackCapacity;
};


#include "AbsStack.inl"
#endif