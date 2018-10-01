/**
*  Course: CMPS 2143 - OOP
*  Assignment: P02
*  Purpose: Overload different operators to work on our vectors
*
*  @author Tyler Roop
*  @version 1.1 10/01/2018
*  @github repo:
*	https://github.com/tarrox1992/2143-OOP-Roop/blob/master/assignments/P02/
*/

#include <iostream>

using namespace std;

class myVector {
private:
	int *vPtr;      // int pointer to array
	int maxSize;    // max size of array
	int minSize;    // min size of array
	int index;      // current location to insert or remove
	int* _resize(int);

public:
	myVector(int size);
	void pushBack(int item);
	void pushBack(int *, int size);
	int popBack();
	double percentFull();
	int* resize(double);
	int* resize(int);

	void print();
	int size();
	void size(int);
	int vSize();

	/**
	* Function operator[]
	*		Overloads [] to allow access to specific elements in a myVector
	*		as if it were an array
	* @param {int} i: element in vector that is being accessed
	* @return myVector.vPtr[i]
	*/
	int& operator[](int i)
	{
		if (i >= maxSize)
		{
			cout << "Array index out of bound, exiting\n";
			exit(0);
		}
		else if (i >= index) {
			cout << "Warning: vector[" << i << "] is undefined ...\n";
		}
		return vPtr[i];
	}


	friend ostream& operator<<(ostream& os, myVector V) {
		for (int i = 0; i<V.index; i++) {
			os << V.vPtr[i] << " ";
		}
		//os<<"test"<<endl;
		return os;
	}

	/**
	* Function operator+
	*   Adds elements in two vectors by eachother and does nothing with
	*   extra elements in larger vector
	* @param {myVector&} rhs: vector whose elements are being subtracted
	* @return myVector
	*/
	myVector operator+(const myVector& rhs) {

		//rhs = vector on the right of the + sign
		//lhs = THIS vector (the one were in)

		int rhsSize = rhs.index;
		int lhsSize = index;
		int max = 0, min = 0;

		// which vector is bigger?
		if (rhsSize > lhsSize)
		{
			max = rhsSize;
			min = lhsSize;
		}
		else
		{
			max = lhsSize;
			min = rhsSize;
		}

		// create a new vector with the bigger size
		myVector newVector(max);

		for (int i = 0; i < max; i++)
		{
			if (i < min)
			{
				newVector.pushBack(rhs.vPtr[i] + vPtr[i]);
			}
			else
			{
				if (max == rhsSize)
				{
					newVector.pushBack(rhs.vPtr[i]);
				}
				else
				{
					newVector.pushBack(vPtr[i]);
				}
			}
		}
		return newVector;
	}

	/**
	* Function operator-
	*   Subtracts elements in two vectors by eachother and does nothing with
	*   extra elements in larger vector
	* @param {myVector&} rhs: vector whose elements are being subtracted
	* @return myVector
	*/
	myVector operator-(const myVector& rhs) {

		//rhs = vector on the right of the - sign
		//lhs = THIS vector (the one were in)

		int rhsSize = rhs.index;
		int lhsSize = index;
		int max = 0, min = 0;

		// which vector is bigger?
		if (rhsSize > lhsSize)
		{
			max = rhsSize;
			min = lhsSize;
		}
		else
		{
			max = lhsSize;
			min = rhsSize;
		}

		// create a new vector with the bigger size
		myVector newVector(max);

		for (int i = 0; i < max; i++)
		{
			if (i < min)
			{
				newVector.pushBack(vPtr[i] - rhs.vPtr[i]);
			}
			else
			{
				if (max == rhsSize)
				{
					newVector.pushBack(rhs.vPtr[i]);
				}
				else
				{
					newVector.pushBack(vPtr[i]);
				}
			}
		}
		return newVector;
	}

	/**
	* Function operator*
	*   Multiplies elements in two vectors by eachother and drops extra
	*   elements in larger vector
	* @param {myVector&} rhs: vector whose elements are multiplied by
	* @return myVector
	*/
	myVector operator*(const myVector& rhs) {

		//rhs = vector on the right of the * sign
		//lhs = THIS vector (the one were in)

		int rhsSize = rhs.index;
		int lhsSize = index;
		int max = 0, min = 0;

		// which vector is bigger?
		if (rhsSize > lhsSize)
		{
			max = rhsSize;
			min = lhsSize;
		}
		else
		{
			max = lhsSize;
			min = rhsSize;
		}

		// create a new vector with the smaller size
		myVector newVector(min);

		for (int i = 0; i < min; i++)
		{
			newVector.pushBack(rhs.vPtr[i] * vPtr[i]);
		}
		return newVector;
	}

	/**
	* Function operator/
	*   Divides elements in two vectors by eachother and drops extra elemnts
	*   in larger vector
	* @param {myVector&} rhs: vector whose elements are in denominator
	* @return myVector
	*/
	myVector operator/(const myVector& rhs) {

		//rhs = vector on the right of the / sign
		//lhs = THIS vector (the one were in)

		int rhsSize = rhs.index;
		int lhsSize = index;
		int max = 0, min = 0;

		// which vector is bigger?
		if (rhsSize > lhsSize)
		{
			max = rhsSize;
			min = lhsSize;
		}
		else
		{
			max = lhsSize;
			min = rhsSize;
		}

		// create a new vector with the smaller size
		myVector newVector(max);

		for (int i = 0; i < min; i++)
		{
				if (rhs.vPtr[i] != 0)
					newVector.pushBack(vPtr[i] / rhs.vPtr[i]);
				else
				{
					cout << "Error, cannot divide by 0";
					exit;
				}
		}
		return newVector;
	}

	/**
	* Function operator==
	*   Assigns the value of one vector equal to an exact copy
	* @param {myVector&} rhs: vector that we are checking the left hand side
	*						  against
	* @return bool is true if values are equal or false if not
	*/
	bool operator==(myVector& rhs) {
		bool isEqual = 1;
		if (index == rhs.index)
		{
			for (int i = 0; i < index; i++)
			{
				if (vPtr[i] == rhs.vPtr[i]) {}
				else isEqual = 0;
			}
		}
		else isEqual = 0;
		return isEqual;
	}

	/**
	* Function operator=
	*   Assigns the value of one vector equal to an exact copy
	* @param {myVector&} equalizer: initial vector that is being copied
	* @return void
	*/
	void operator=(myVector& equalizer)
	{
		vPtr = new int[equalizer.maxSize];
		index = equalizer.index;
		maxSize = equalizer.maxSize;
		minSize = equalizer.minSize;
		for (int i = 0; i < index; i++)
		{
			vPtr[i] = equalizer.vPtr[i];
		}
	}
};

/**
* Function constructor
*   Sets up the vector
* @param {int} size : initial size of vector
* @return void
*/
myVector::myVector(int size) {
	maxSize = size;
	minSize = size;
	// create the array of vSize
	vPtr = new int[maxSize];
	index = 0;
}

/**
* Function print
*   Prints the current values in the vector
* @param void
* @return void
*/
void myVector::print() {
	for (int i = 0; i<index; i++) {
		cout << vPtr[i] << " ";
	}
	cout << endl;
}

/**
* Function pushBack
*   Adds value to vector
* @param {int} item : integer value
* @return void
*/
void myVector::pushBack(int item) {
	if (index >= maxSize) {
		vPtr = resize(1.5);
	}
	vPtr[index++] = item;
}

/**
* Function pushBack
*   Overloaded pushBack to add an array of ints to vector
* @param {int*} size : address of first element in array
* @param {int} size : size of array
* @return void
*/
void myVector::pushBack(int *A, int size)
{
	for (int i = 0; i < size; i++)
	{
		pushBack(A[i]);
	}
}

/**
* Function popBack
*   Returns value from vector
* @param none
* @return {int} : last item on vector
*/
int myVector::popBack() {

	index--;

	if (index < 0) {
		//dammit
	}

	if (percentFull() <= .4) {
		vPtr = resize(.5);
	}

	return vPtr[index];
}

/**
* Function resize
*   Resizes our vector based on passed in ratio
* @param {double} ratio : new array size
* @return {int*} : pointer to new array
*/
int* myVector::resize(double ratio) {
	// figure out what our new size is, bigger or smaller
	int newSize = maxSize * ratio;

	return _resize(newSize);
}

int* myVector::resize(int size) {

	return _resize(size);

}

int* myVector::_resize(int newSize) {
	// Lets keep our vector above some minimum size
	if (newSize < minSize) {
		newSize = minSize;
	}

	// allocate new bigger vector
	int* vBigger = new int[newSize];

	//copy everything over
	for (int i = 0; i<index; i++) {
		vBigger[i] = vPtr[i];
	}

	// update new max size
	maxSize = newSize;

	// delete old memory
	delete[] vPtr;

	//return ptr to new memory
	return vBigger;
}

/**
* Function percentFull
*   helper function to calculate how full vector is
* @param none
* @return {double} : how full vector is
*/
double myVector::percentFull() {
	return double(index) / double(maxSize);
}

/**
* Function size
*    Returns number of current items in vector
* @param none
* @return {int} : num items
*/
int myVector::size() {
	return index;
}

/**
* Function size
*    Returns number of current items in vector
* @param none
* @return {int} : num items
*/
void myVector::size(int newSize) {
	vPtr = _resize(newSize);
}

/**
* Function vSize
*    Returns actual size of allocated memory
* @param none
* @return {int} : mem size
*/
int myVector::vSize() {
	return maxSize;
}
