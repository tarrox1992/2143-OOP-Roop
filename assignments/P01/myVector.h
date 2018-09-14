#include <iostream>
#include <string>

using namespace std;

// class to mimic c++ vector

class myVector {
private:
	int *theVector;
	int *tempV;
	int *tempP;
	int oSize;
	int index;
	double perFull;
public:
	myVector(int size);
	void pushBack(int item);
	int popBack();
	void print();
	void pushBack(string ohsowrong);
	int vSize;
};
