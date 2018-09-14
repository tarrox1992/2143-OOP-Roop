#include <iostream>
#include "myVector.h"
#include <string>

using namespace std;

/**
*   Creates an instance of the  myVector class
*
*   @param {int} size : The initial size of the vector
*/

myVector::myVector(int size)
{
	oSize = size;
	vSize = size;
	theVector = new int[vSize];
	index = 0;
}

/**
*   Adds a variable to the end of the vector and increases the
*   size of the vector if it is full
*
*   @param {int} item : The variable to be added
*/

void myVector::pushBack(int item)
{
	// checks whether vector is full, and if so increases size by
	// a factor of 1.5
	if (index == vSize)
	{
		tempV = new int[(double)vSize * 1.5];
		for (int i = 0; i < vSize; i++)
		{
			tempV[i] = theVector[i];
		}
		vSize = vSize + ((double)vSize / 2);
		tempP = theVector;
		theVector = tempV;
		delete tempP;
	}
	// puts variable onto end of vector
	theVector[index] = item;

	// increments index marker of vector
	index++;

}

/**
*   Returns the last value of the vector, or false if the
*   vector is empty. Also shrinks size of vector if the
*	vector becomes smaller than 40% of its current size
*/
int myVector::popBack()
{
	// checks if vector is not empty
	if (index != 0)
	{
		// sets return variable to the last value in vector
		int Val = theVector[index - 1];

		// decrements index marker of vector
		index--;

		// checks how full the vector is
		perFull = (double)index / (double)vSize;
		
		// decreases size of vector if less than 40% full
		if (perFull <= .4)
		{
			if ((vSize / 2) > oSize)
			{
				tempV = new int[vSize / 2];
				vSize /= 2;
			}
			else
			{
				tempV = new int[oSize];
				vSize = oSize;
			}
			for (int i = 0; i < index; i++)
			{
				tempV[i] = theVector[i];
			}
			tempP = theVector;
			theVector = tempV;
			delete tempP;
		}
		// returns the last variable
		return Val;
	}
	else
	{
		// return if empty
		return false;
	}
}

//  Prints every variable in the vector.
void myVector::print()
{
	for (int i = 0; i < index; i++)
	{
		cout << theVector[i] << " ";
	}
	cout << '\n';
}

/**
*   Overloaded pushBack in case someone tries to push string
*	onto vector
*
*   @param {string} ohsowrong : The string attempting to be pushed
*/
void myVector::pushBack(string ohsowrong)
{
	cout << "Error, this vector is not for strings\n";
	return;
}
