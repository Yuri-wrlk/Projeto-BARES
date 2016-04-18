#include <iostream>
#include <algorithm>
#include <cstring>
#include <stdexcept>

#ifndef _STACK_INT_
#define _STACK_INT_

class StackInt 
{
	public:
		StackInt (size_t = 50);
		//Default constructor

		virtual ~ StackInt () { /* Empty */ } 
		// Default destructor

		// Basic members
		void push ( const int &);
		int pop ( );
		int top ( ) const;
		bool isEmpty ( ) const;
		void makeEmpty ( );
	
	private:
		// Only to be used in class
		void resize ( );

		// Disable copy constructor
		StackInt ( const StackInt & ) { /* Empty */ }

		// Class variables
		int * myStack;
		size_t stackSize;
		size_t stackCapacity;

};

#endif