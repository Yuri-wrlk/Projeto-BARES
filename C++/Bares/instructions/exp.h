#include "iostream"	
#include "string"
#include "fstream"

#ifndef _EXPRESSION_
#define _EXPRESSION_


class Expression
{
private:
	using size_type = size_t;
	
	// Variables used in queue ADT
	std::string * line;			// Pointer to an sting array dynamically allocated
	size_type lineSize;			// Keeps the actual number of expressions inside the array
	size_type lineCapacity;		// Keeps array's maximun capacity
	int first;					// Position of the queue's first element
	int last;					// Position of the queue's last element

	// Both are going to be used in parsing
	char operators [8] = {  '(' , ')' , '^' , '*' , '/' , '%' , '+' , '-'}; 

public:
	//Constructor
	Expression (std::string, size_type = 30);

	//Destructor
	~Expression(){ delete [] line; }

	// Common methods to the queue ADT
	void enqueue ( std::string );
	std::string dequeue ( );
	std::string getFront ( ) const;
	bool isEmpty ( ) const;
	void makeEmpty ( );
	void printQueue ( );
	// Only to be used in class
	//void doubleSize (); //Faulty implementation, needs to be fixed

	//Methods unique to expression division
	void tokenize(const std::string &);
	bool isOperator(char);
	bool isInteger(char);
};

#include "exp.inl"

#endif