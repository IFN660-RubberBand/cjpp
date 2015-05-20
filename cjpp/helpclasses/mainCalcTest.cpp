#include <stdio.h>
#include <iostream>
#include "MathFuncsLib.h"
//#include "Values.h"
#include <typeinfo>

using namespace std;

/*
 * Compile: g++ -x c++ -std=c++14 mainCalcTest.cpp -o mainCalcTest && ./mainCalcTest
 * Type checking is possible with "typeid(...).name()" (replace the "..." with your input). All the used 
 * values need to be allocated so you can't use an integer as a value but you can use a predefined 
 * variable with a number as a value. The given output is not human readable so you need to convert the
 * compiled program using c++filt -t. Example: "./mainCalcTest | c++filt -t".
 */
int main(){

	int i40 = 40;
	int i2 = 2;
    float f40 = 40.1;
    float f2 = 2.1;
    string s40 = "40";
    string s2 = "2";
    
    cout << "new string + string: " << MathFuncs::addV2(s40, i2)->val << endl;
    cout << "new float + int: " << dynamic_cast<FloatValue*>(MathFuncs::addV2(f40, i2))->val << endl;
    
    // Use of classed in Values.h
//    IntValue* ival40 = new IntValue(&i40);
//    IntValue* ival2 = new IntValue(&i2);
    
//    Value* uValue = new UndefinedValue();
//    Value* value40 = new FloatValue(40.4);
//    Value* value2 = new StringValue("2");
//    Value* value40 = new IntegerValue(*i40);
//    Value* value2 = new IntegerValue(*i2);

//    IntegerValue* iValue40 = dynamic_cast<IntegerValue*>(value40);
//    IntegerValue* iValue2 = dynamic_cast<IntegerValue*>(value2);
    
//    cout << "TEST: " << iValue40->returnType() << endl;
//    cout << "TEST: " << iValue2->returnType() << endl;
    
//    cout << "MEMORY: " << &value40 << endl;
    
//    cout << "new    integer + integer: " << MathFuncs::addV(value40, value2) << endl;
    
//    IntegerValue* ival = dynamic_cast<IntegerValue*>(MathFuncs::addV(value40, value2));
//    Value* vval = MathFuncs::addV(value40, value2);
    
//    cout << "new    IntegerValue + IntegerValue: " << MathFuncs::addV(value40, value2)->val;
//    cout << "new    IntegerValue + IntegerValue: " << ival->val << endl;
//    cout << "new    IntegerValue + IntegerValue: " << vval->val;

	cout << endl << "> Additions" << endl;
	cout << "string + integer: " << MathFuncs::add("Hai", 4) << endl;
	cout << "integer + string: " << MathFuncs::add(4, "Hai") << endl;
	cout << "string + double: " << MathFuncs::add("Hai", 4.2) << endl;
	cout << "double + string: " << MathFuncs::add(4, "Hai") << endl;
	cout << "string + string: " << MathFuncs::add("Hello", "World!") << endl;
	cout << "integer + integer: " <<MathFuncs::add(2, 4) << endl;
    cout << "double + integer: " <<MathFuncs::add(2.0, 4) << endl;
    cout << "integer + double: " <<MathFuncs::add(2, 4.0) << endl;
    
    cout << endl << "> Subtraction" << endl;
    cout << "string - integer: " << MathFuncs::sub("Hai", 4) << endl;
    cout << "integer - string: " << MathFuncs::sub(4, "Hai") << endl;
    cout << "string - double: " << MathFuncs::sub("Hai", 4.2) << endl;
    cout << "double - string: " << MathFuncs::sub(4, "Hai") << endl;
    cout << "string - string: " << MathFuncs::sub("Hello", "World!") << endl;
    cout << "integer - integer: " <<MathFuncs::sub(2, 4) << endl;

	cout <<  endl << "Comparators" << endl;
	cout << "2 < 4: " << MathFuncs::lssthan(2, 4) << endl;
	cout << "2.4 < 2.5: " << MathFuncs::lssthan(2.4, 2.5) << endl;
	cout << "2 > 4: " << MathFuncs::gtrthan(2, 4) << endl;
	cout << "2 == 2.0: " << MathFuncs::equalto(2, 2.0) << endl;
	cout << "2 <= 2: " << MathFuncs::leqthan(2, 2) << endl;
	cout << "\"2\" > 1: " << MathFuncs::gtrthan("2", 1) << endl;
	// cout << "integer === string: " << MathFuncs::cmp(2, "2", IDENT) << endl;

	printf("\nEND\n");

}
