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

	// cout << "(Old) Only numbers: " << MathFuncs::Add(1, 2) << endl << endl;
	// cout << "(Old) Only strings: " << MathFuncs::AddString("Left Val", "Right Val") << endl << endl;

	// cout << MathFuncs::MathFuncs::AddObject("Left Val", "Right Val") << endl;
	// cout << MathFuncs::AddObject("Test", num2) << endl;
	// cout << "Is of type: " << typeid((MathFuncs::AddObject("Test", num2))).name() << endl;

	cout << "Additions" << endl << endl;
	cout << "string + integer: " << MathFuncs::add("Hai", 4) << endl << endl;
	cout << "integer + string: " << MathFuncs::add(4, "Hai") << endl << endl;
	cout << "string + double: " << MathFuncs::add("Hai", 4.2) << endl << endl;
	cout << "double + string: " << MathFuncs::add(4, "Hai") << endl << endl;
	cout << "string + string: " << MathFuncs::add("Hello", "World!") << endl << endl;
	cout << "integer + integer: " <<MathFuncs::add(2, 4) << endl << endl;

	cout << "Comparators" << endl << endl;
	cout << "2 < 4: " << MathFuncs::lssthan(2, 4) << endl << endl;
	cout << "2.4 < 2.5: " << MathFuncs::lssthan(2.4, 2.5) << endl << endl;
	cout << "2 > 4: " << MathFuncs::gtrthan(2, 4) << endl << endl;
	cout << "2 == 2.0: " << MathFuncs::equalto(2, 2.0) << endl << endl;
	cout << "2 <= 2: " << MathFuncs::leqthan(2, 2) << endl << endl;
	cout << "\"2\" > 1: " << MathFuncs::gtrthan("2", 1) << endl << endl;
	// cout << "integer === string: " << MathFuncs::cmp(2, "2", IDENT) << endl << endl;

	printf("\nEND\n");

}
