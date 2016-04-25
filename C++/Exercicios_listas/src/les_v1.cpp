// This is a stub code (or skeleton code) just to allow the first compilation.

#include <iostream>
#include "les_v1.h"

using namespace std;

//! Prints the list.
/*! This a debugging function that prints the list content.
 *  @param _pAIL Pointer to the head of the list. It NULL, list is empty.
 */
void print( SNPtr _pAIL )
{
    if (_pAIL == nullptr)
    {
        std::cout << "\nThe list is empty! Nothing here to be printed." << std::endl;
        return;
    }

    SNPtr tail = _pAIL;

    std::cout << std::endl;
    for (auto i (0); i < length(_pAIL); ++i)
    {
        std::cout << "=====";
    }
    std::cout << std::endl;

    // Printing the list's numbers while the end is not reached
    while(tail != nullptr)
    {
        std::cout << " " << tail->miData;
        tail = tail->mpNext;
    }

    std::cout << std::endl;
    for (auto i (0); i < length(_pAIL); ++i)
    {
        std::cout << "=====";
    }
    std::cout << std::endl;
    

}

//! Length of the list.
/*! Calculates and return the length of the list. Length is zero, if list is empty.
 *  @param _pAIL Pointer to the head of the list. It NULL, list is empty.
 *  @return The length.
 */
int length( SNPtr _pAIL )
{
    int count = 0;

    while(_pAIL != nullptr)
    {
        _pAIL = _pAIL->mpNext;
        count++;
    }

    return count;
}


bool empty( SNPtr _pAIL )
{
    return (_pAIL == nullptr);
}


void clear( SNPtr & _pAIL )
{
    if(_pAIL != nullptr)
    {
        SNPtr nextRemoval = _pAIL->mpNext;

        do
        {
            delete _pAIL;
            _pAIL = nextRemoval;
            if(nextRemoval != nullptr)
                nextRemoval = nextRemoval->mpNext;
        } while(_pAIL != nullptr);  
    
    }  
}


bool front( SNPtr _pAIL, int & _retrievedVal )
{
    if(_pAIL == nullptr)
        return false;

    _retrievedVal = _pAIL->miData;
    return true;
}


bool back( SNPtr _pAIL, int & _retrievedVal )
{
    if(_pAIL == nullptr)
        return false;

    while(_pAIL->mpNext != nullptr)
    {
        _pAIL = _pAIL->mpNext;
    }

    _retrievedVal = _pAIL->miData;
    return true;
}


bool pushFront( SNPtr & _pAIL, int _newVal )
{
    SNPtr front = nullptr;
    
    try
    {
        front = new SLLNode;    
    }
    catch (const std::bad_alloc & e)
    {
        return false;
    }
    
    front->miData = _newVal;
    front->mpNext = _pAIL;
    _pAIL = front;
    return true;
}


bool pushBack( SNPtr & _pAIL, int _newVal )
{
    SNPtr candidate = nullptr;
    
    try
    {
        candidate = new SLLNode;    
    }
    catch (const std::bad_alloc & e)
    {
        return false;
    }

    if(_pAIL == nullptr)
    {
    	candidate->miData = _newVal;
    	candidate->mpNext = nullptr;
        _pAIL = candidate;
    }

    else
    {
        SNPtr work = _pAIL;

        while(work->mpNext != nullptr)
        {
            work = work->mpNext;
        }

        candidate->miData = _newVal;
        candidate->mpNext = nullptr;
        work->mpNext = candidate;    
    }
    return true;
}


bool popFront( SNPtr & _pAIL, int & _retrievedVal )
{
 	if(_pAIL == nullptr)
 		return false;

 	SNPtr work = _pAIL;
	_retrievedVal = _pAIL->miData;
	_pAIL =  _pAIL->mpNext;
	delete [] work;

    return true;
}


bool popBack( SNPtr & _pAIL, int& _retrievedVal )
{
	if(_pAIL == nullptr)
 		return false;

	SNPtr work = nullptr;
	SNPtr work2 = _pAIL;
    while(work2->mpNext != nullptr)
    {
    	work = work2;
        work2 = work2->mpNext;
    } 	
    _retrievedVal = work2->miData;
    delete [] work2;
    work->mpNext = nullptr;
    return true;
}


SNPtr find( SNPtr _pAIL, int _targetVal )
{
	if(_pAIL == nullptr)
    	return NULL;
    else if(_pAIL->miData == _targetVal)
    {
    	std::cout << "The target value is in the first position" << std::endl;
    	return NULL;
    }

    while (_pAIL->mpNext != nullptr)
    {
    	if(_pAIL->mpNext->miData == _targetVal)
    		return _pAIL;
    }

   	return NULL;
}


bool insert( SNPtr & _pAIL, SNPtr _pAnte, int _newVal )
{

   	
    SNPtr candidate = nullptr;
   	try
    {
       	candidate = new SLLNode;    
    }
    catch (const std::bad_alloc & e)
    {
       	return false;
    }
    
    candidate->miData = _newVal;
    candidate->mpNext = nullptr;

   	if(_pAnte == nullptr)
   	{	
    	candidate->mpNext = _pAIL->mpNext;
    	_pAIL->mpNext = candidate;
    	return true;
   	}
   	else
   	{
   		SNPtr work = _pAIL;
   		while(work == _pAnte)
   		{
   			work = work->mpNext;
   		}
   		candidate->mpNext = work->mpNext;
   		work->mpNext = candidate;
   	}
    return true;
}


bool remove( SNPtr & _pAIL, SNPtr _pAnte, int & _retrievedVal )
{
	if (_pAIL == nullptr)
		return false;

	if(_pAnte == nullptr)
	{
		_retrievedVal = _pAIL->miData;
		SNPtr work = _pAIL;
		_pAIL = _pAIL->mpNext;
		delete [] work;
	}
	
	SNPtr work = _pAIL;
	SNPtr work2 = nullptr;
	while (work != _pAnte && work->mpNext != nullptr)
	{
		work = work->mpNext;
	}
	if (work == _pAnte)
	{
		work2 = work->mpNext;
		_retrievedVal = work2->miData;
		work->mpNext = work2->mpNext;
		delete [] work2;
		return true;
	}
    return false;
}


//**** ===================[ End of les_v1.cpp ]=================== ****// 
