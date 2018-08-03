//============================================================================
// Name        : CMoon.cpp
// Author      : nadong
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "Thread100.h"
#include <iostream>
using namespace std;


int main() {
//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	Thread100 thread100;
//	thread100.testNonBlock();
	thread100.testBlock();
	return 0;
}
