#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstring>

#include "AbsQueue.h"

#ifndef _QUEUE_AR_
#define _QUEUE_AR_

template < class Object >
class QueueAr : AbsQueue < Object >
{
	public:
		// Class constructor
		QueueAr (size_t = 20);

		~QueueAr () { delete [] myQueue; } 

		// Basic members
		void enqueue ( const Object & x );
		Object dequeue ( );
		Object getFront ( ) const;
		bool isEmpty ( ) const;
		void makeEmpty ( );

	private:
		// Only to be used in class
		void doubleSize ();

		// Class variables
		Object * myQueue;
		size_t queueSize;
		size_t queueCapacity;
		int first;
		int last; 

};

#include "queuear.inl"

#endif