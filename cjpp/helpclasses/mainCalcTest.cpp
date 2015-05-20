#include <stdio.h>
#include <iostream>
#include "MathFuncsLib.h"
//#include "Values.h"
#include <typeinfo>
#include "value.h"
#include "Scope.h"

using namespace std;

/*
 * Compile: g++ -x c++ -std=c++14 mainCalcTest.cpp -o mainCalcTest && ./mainCalcTest
 * Type checking is possible with "typeid(...).name()" (replace the "..." with your input). All the used 
 * values need to be allocated so you can't use an integer as a value but you can use a predefined 
 * variable with a number as a value. The given output is not human readable so you need to convert the
 * compiled program using c++filt -t. Example: "./mainCalcTest | c++filt -t".
 */
int main(int argc, char* argv[]){

	int num1 = 4;
	int num2 = 2;
    
    Scope* currentscope = new Scope();
    
//    Value* uValue = new UndefinedValue();
//    Value* value40 = new FloatValue(40.4);
//    Value* value2 = new StringValue("2");
    Value* value40 = new IntegerValue(40);
    Value* value2 = new IntegerValue(2);
    Value* value10 = new StringValue("10");
    Value* value24 = new FloatValue(2.4);
    Value* value25 = new FloatValue(2.5);

//    IntegerValue* iValue40 = dynamic_cast<IntegerValue*>(value40);
//    IntegerValue* iValue2 = dynamic_cast<IntegerValue*>(value2);
    
//    cout << "TEST: " << iValue40->returnType() << endl;
//    cout << "TEST: " << iValue2->returnType() << endl;
    
//    cout << "MEMORY: " << &value40 << endl;
    
//    cout << "new    integer + integer: " << MathFuncs::addV(value40, value2) << endl;
    
    cout << "new    IntegerValue + IntegerValue: " << MathFuncs::addV(value40, value2)->val << endl;
    cout << value40 << endl;
    cout << value40->val << endl;
    cout << value40->returnType() << endl;
    

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
	cout << "True is: " << true << endl;
	cout << "False is: " << false << endl;
	cout << "2 < 40: " << MathFuncs::lssthan(value2, value40) << endl;
	cout << "2 > 40: " << MathFuncs::gtrthan(value2, value40) << endl;
	cout << "40 > 2: " << MathFuncs::gtrthan(value40, value2) << endl;
	cout << "\"10\" < 2: " << MathFuncs::lssthan(value10, value2) << endl;
	cout << "\"10\" > 2: " << MathFuncs::gtrthan(value10, value2) << endl;
	cout << "2 == 2: " << MathFuncs::equalto(value2, value2) << endl;
	cout << "2 != 40: " << MathFuncs::neqto(value2, value40) << endl;
	cout << "2.4 < 2.5: " << MathFuncs::lssthan(value24, value25) << endl;

	printf("\nEND\n");

}
