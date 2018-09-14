/**
*  Course: CMPS 2143 - OOP
*  Assignment: P01
*  Purpose: Create a sort of vector using an array and manipulate it
*
*  @author Tyler Roop
*  @version 1.1 9/14/18
*/

#include <iostream>
#include "myVector.h"
#include <string>

using namespace std;

int main() {

	// declares a vectorof size 10
	myVector V(10);

	// prints statement if vector is empty
	if (!V.popBack())
		cout << "There's nothing there!\n";
	// adds three variables to vector
	V.pushBack(13);
	V.pushBack(31);
	V.pushBack(73);

	// prints vector
	V.print();

	// adds 10000 variables to vector
	for (int j = 0; j < 10000; j++)
		V.pushBack(j % 7);

	// prints size of vector
	cout << V.vSize << '\n';

	// removes 9998 variables from vector
	for (int j = 0; j < 9998; j++)
		V.popBack();

	// prints size of vector
	cout << V.vSize << '\n';

	// attempts to add string to vector
	V.pushBack("Hey");

	// pauses program to check results then ends program
	system("pause");
	return 0;
}
