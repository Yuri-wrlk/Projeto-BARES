//Class methods implementation

template < class Object >
QueueAr< Object >::QueueAr (size_t _capacity) 
{
	if(_capacity == 0)
		throw std::out_of_range("Can't initiate with zero elements!");
	myQueue = new Object [_capacity];
	queueCapacity = _capacity;
	queueSize = 0;
	first = -1;
	last = -1;
}

template < class Object >
void QueueAr< Object >::enqueue ( const Object & _candidate )
{
	if(queueSize == queueCapacity)
	{
		doubleSize();
		myQueue[(last + 1) % queueCapacity] = _candidate;
		last = (last + 1) % queueCapacity;
		queueSize++; 
	}
	else if(queueSize == 0)
	{
		myQueue[0] = _candidate;
		queueSize++;
		first = 0;
		last = 0;
	}
	else
	{
		myQueue[(last + 1) % queueCapacity] = _candidate;
		last = (last + 1) % queueCapacity;
		queueSize++;	
	}
}

template < class Object >
Object QueueAr< Object >::dequeue ( )
{
	if(queueSize == 0)
	{
		throw std::out_of_range ("There is no element to remove!");
	}

	Object tempObj = myQueue[first];
	first = (first + 1) % queueCapacity;
	queueSize--;
	
	if(queueSize == 0)
	{
		first = -1;
		last = -1;
	}

	return tempObj;
}

template < class Object >
Object QueueAr< Object >::getFront ( ) const
{
	return myQueue[first];
}


template < class Object >
bool QueueAr< Object >::isEmpty ( ) const
{
	return (queueSize == 0);
}

template < class Object >
void QueueAr< Object >::makeEmpty ( )
{
	queueSize = 0;
	first = -1;
	last = -1;
}

template < class Object >
void QueueAr< Object >::doubleSize( )
{
	size_t _newCapacity = 2 * queueCapacity;
	Object * _newArray = new Object [_newCapacity];
		
	memcpy(_newArray, myQueue, sizeof(Object) * queueSize);

	if(last < first)
	{
		auto i (1u);
		for(; i <= (queueCapacity - first); ++i)
		{
			_newArray[_newCapacity - i] = _newArray[queueCapacity - i];
		}
		last = _newCapacity - i  + 1;
	}
	
	queueCapacity = _newCapacity;
	delete[] myQueue;
	myQueue = _newArray;
}
