#ifndef _STACKAR_H_
#define _STACKAR_H_

#include "AbsStack.h" 
// Inclui a interface abstrata da pilha .
// Implementando interface via herança .

template < typename Object >
class StackAr : public AbsStack < Object > 
{
	public:
		StackAr(size_t _size = 10) : AbsStack < Object > (_size) 
		{ /* Empty */ }

		void push(const Object &);
		Object pop ( );
		Object top ( ) const;

	private:

};

// Includes the class implementation from the next file
#include "stackar.inl"

#endif

