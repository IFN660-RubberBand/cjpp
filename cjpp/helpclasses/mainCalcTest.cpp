#include <stdio.h>
#include <iostream>
#include "MathFuncsLib.h"
#include <typeinfo>

using namespace std;

/*
 * Compile: g++ -x c++ -std=c++14 mainCalcTest.cpp -o mainCalcTest && ./mainCalcTest
 */
int main(){

	int num1 = 4;
	int num2 = 2;
	// cout << "Is of type: " << typeid((MathFuncs::AddObject("Test", num2))).name() << endl;

	cout << endl << "> Additions" << endl;
	cout << "string + integer: " << MathFuncs::add("Hai", 4) << endl;
	cout << "integer + string: " << MathFuncs::add(4, "Hai") << endl;
	cout << "string + double: " << MathFuncs::add("Hai", 4.2) << endl;
	cout << "double + string: " << MathFuncs::add(4, "Hai") << endl;
	cout << "string + string: " << MathFuncs::add("Hello", "World!") << endl;
	cout << "integer + integer: " <<MathFuncs::add(2, 4) << endl;
    
    cout << endl << "> Subtraction" << endl;
    cout << "string - integer: " << MathFuncs::sub("Hai", 4) << endl;
    cout << "integer - string: " << MathFuncs::sub(4, "Hai") << endl;
    cout << "string - double: " << MathFuncs::sub("Hai", 4.2) << endl;
    cout << "double - string: " << MathFuncs::sub(4, "Hai") << endl;
    cout << "string - string: " << MathFuncs::sub("Hello", "World!") << endl;
    cout << "integer - integer: " <<MathFuncs::sub(2, 4) << endl;

	cout << endl << "Comparators" << endl;
	cout << "2 < 4: " << MathFuncs::lssthan(2, 4) << endl;
	cout << "2.4 < 2.5: " << MathFuncs::lssthan(2.4, 2.5) << endl;
	// cout << "2 > 4: " << MathFuncs::gtrthan(2, 4) << endl;
	// cout << "2 == 2: " << MathFuncs::equalto(2, 2) << endl;
	// cout << "2 <= 2: " << MathFuncs::leqthan(2, 2) << endl;
	// cout << "integer === string: " << MathFuncs::cmp(2, "2", IDENT) << endl;

	printf("\nEND\n");

}
