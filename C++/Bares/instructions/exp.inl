Expression::Expression (std::string _expline, size_type _sz) :
		lineSize (0),
		lineCapacity (_sz),
		first (-1),
		last (-1)
{
	line = new std::string [lineCapacity];
	tokenize(_expline);
}

//Destructor
//Expression::~Expression();


// Common methods to the queue ADT
void Expression::enqueue ( std::string x )
{
	/*if(queueSize == queueCapacity)
	{
		doubleSize();
		myQueue[(last + 1) % queueCapacity] = _candidate;
		last = (last + 1) % queueCapacity;
		queueSize++; 
	}*/
	if(lineSize == 0)
	{
		line[0] = x;
		lineSize++;
		first++;
		last++;
	}
	else
	{
		line[(last + 1) % lineCapacity] = x;
		last = (last + 1) % lineCapacity;
		lineSize++;	
	}
}
/*
std::string Expression::dequeue ( );
std::string Expression::getFront ( ) const;
bool Expression::isEmpty ( ) const;
void Expression::makeEmpty ( );
void Expression::printQueue ( );
// Only to be used in class
//void doubleSize (); //Faulty implementation, needs to be fixed
*/

//Methods unique to expression division
void Expression::tokenize(const std::string & _expline)
{
	std::string aux = "";
	
	for(auto i (0u); i < _expline.length(); ++i)
	{
		if(_expline[i] == ' ')
			continue;
		else if ( isOperator(_expline[i]) )
		{
			aux = aux + _expline[i];
			enqueue( aux );
			aux = "";
		}
		else if (isInteger(_expline[i])) 
		{
			aux = aux + _expline[i];
			while(i + 1 < _expline.length() && isInteger(_expline[i + 1]))
			{	
				aux = aux + _expline[++i];
			}
			enqueue(aux);
			aux = "";
		}
	}

	std::cout << "The tokenized expression is:\n";
	for ( auto i (0u); i < lineSize; ++i)
		{
			std::cout << line[i];
		}	
	std::cout << "\n";
}

bool Expression::isOperator(char candidate)
{
	for (int i = 0; i < 8; ++i)
	{
		if (candidate == operators[i])
			return true;
	}
	return false;
}

bool Expression::isInteger(char candidate)
{
	if (candidate > 47 && candidate < 58)
		return true;
	return false;
}
