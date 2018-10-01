/**
*  Course: CMPS 2143 - OOP
*  Assignment: P02
*  Purpose: Overload different operators to work on our vectors
*
*  @author Tyler Roop
*  @version 1.1 10/01/2018
*  @github repo: https://github.com/tarrox1992/2143-OOP-Roop/blob/master/assignments/P02/
*/

#include <iostream>
#include "myVector.h"

using namespace std;

int main() {
	// vectors to be experimented with
	myVector V1(10);
	myVector V2(20);

	// int and array of int to push onto vector
	int size = 2;
	int * Ary;
	Ary = new int[size];
	Ary[0] = 69;
	Ary[1] = 40;

	// randomly fills vectors
	for (int i = 0; i<5; i++)
	{
		V1.pushBack(rand() % 100);
	}

	for (int i = 0; i<7; i++)
	{
		V2.pushBack(rand() % 100);
	}

	cout << V1 << " V1" << endl;
	cout << V2 << " V2" << endl;

	// Addition testing
	myVector V3 = V1 + V2;
	cout << V3 << " added vectors V3 and V7" << endl;

	// subtraction testing
	myVector V4 = V1 - V2;
	cout << V4 << " subtracted vectors V4" << endl;

	// multiplication testing
	myVector V5 = V1 * V2;
	cout << V5 << " multiplied vectors V5" << endl;

	// division testing
	myVector V6 = V1 / V2;
	cout << V6 << " divided vectors V6" << endl;

	myVector V7 = V2 + V1;

	// testing for check if equal
	if (V1 == V2)
		cout << "V1 and V2 are equal\n";
	else
		cout << "V1 and V2 are not equal\n";

	if (V3 == V7)
		cout << "V3 and V7 are equal\n";
	else
		cout << "V3 and V7 are not equal\n";

	// testing equal assignment
	myVector V8 = V7;
	cout << V8 << endl << V7 << endl << "Equalized vectors V8\n";

	// testing for pushing an array onto the vector
	V8.pushBack(Ary, size);
	cout << V8 << endl;

	system("pause");

	return 0;
}
