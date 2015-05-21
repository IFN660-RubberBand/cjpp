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

    Value* nival40 = new NumberValue(40);
    Value* nival2 = new NumberValue(2);
    Value* nfval40one = new NumberValue(40.1);
    Value* nfval40two = new NumberValue(40.2);
    Value* nfval2one = new NumberValue(2.1);
    Value* nfval2two = new NumberValue(2.2);
    Value* sval40 = new StringValue("40");
    Value* sval2 = new StringValue("2");
    Value* sval0 = new StringValue("0");
    Value* svalHello = new StringValue("Hello");
    Value* svalWorld = new StringValue("World");
    Value* svalSpace = new StringValue(" ");

    cout << "> Addtion (new addV2 method)" << endl;
    cout << "int + int: " << MathFuncs::addV2(nival40, nival2)->toFloat() << endl;
    
    // Scope* currentscope = new Scope();

    // cout << endl << "> Additions (new add method)" << endl;
    // cout << "new string + string: " << dynamic_cast<StringValue*>(MathFuncs::addV(s40, i2))->val << endl;
    // cout << "new float + int: " << dynamic_cast<FloatValue*>(MathFuncs::addV(f40, i2))->val << endl;
    // cout << "new int + int: " << dynamic_cast<IntegerValue*>(MathFuncs::addV(i40, i2))->val << endl;
    
    // Use of classed in Values.h
//    IntValue* ival40 = new IntValue(&i40);
//    IntValue* ival2 = new IntValue(&i2);
    
//    Value* uValue = new UndefinedValue();
//    Value* value40 = new FloatValue(40.4);
//    Value* value2 = new StringValue("2");
    // Value* value40 = new IntegerValue(40);
    // Value* value2 = new IntegerValue(2);
    // Value* value10 = new StringValue("10");
    // Value* value24 = new FloatValue(2.4);
    // Value* value25 = new FloatValue(2.5);

//    IntegerValue* iValue40 = dynamic_cast<IntegerValue*>(value40);
//    IntegerValue* iValue2 = dynamic_cast<IntegerValue*>(value2);
    
//    cout << "TEST: " << iValue40->returnType() << endl;
//    cout << "TEST: " << iValue2->returnType() << endl;
    
//    cout << "MEMORY: " << &value40 << endl;
    
//    cout << "new    integer + integer: " << MathFuncs::addV(value40, value2) << endl;
    
//    IntegerValue* ival = dynamic_cast<IntegerValue*>(MathFuncs::addV(value40, value2));
//    Value* vval = MathFuncs::addV(value40, value2);
//    cout << "new    IntegerValue + IntegerValue: " << MathFuncs::addV(value40, value2)->val << endl;
//    cout << value40 << endl;
//    cout << value40->val << endl;
//    cout << value40->returnType() << endl;
    
//    cout << "new    IntegerValue + IntegerValue: " << MathFuncs::addV(value40, value2)->val;
//    cout << "new    IntegerValue + IntegerValue: " << ival->val << endl;
//    cout << "new    IntegerValue + IntegerValue: " << vval->val;

	cout << endl << "> Additions (old add method)" << endl;
	cout << "string + integer: " << MathFuncs::add("Hai", 4) << endl;
	cout << "integer + string: " << MathFuncs::add(4, "Hai") << endl;
	cout << "string + double: " << MathFuncs::add("Hai", 4.2) << endl;
	cout << "double + string: " << MathFuncs::add(4, "Hai") << endl;
	cout << "string + string: " << MathFuncs::add("Hello", "World!") << endl;
	cout << "integer + integer: " <<MathFuncs::add(2, 4) << endl;
    cout << "double + integer: " <<MathFuncs::add(2.0, 4) << endl;
    cout << "integer + double: " <<MathFuncs::add(2, 4.0) << endl;
    
    cout << endl << "> Subtraction (old add method)" << endl;
    cout << "string - integer: " << MathFuncs::sub("Hai", 4) << endl;
    cout << "integer - string: " << MathFuncs::sub(4, "Hai") << endl;
    cout << "string - double: " << MathFuncs::sub("Hai", 4.2) << endl;
    cout << "double - string: " << MathFuncs::sub(4, "Hai") << endl;
    cout << "string - string: " << MathFuncs::sub("Hello", "World!") << endl;
    cout << "integer - integer: " <<MathFuncs::sub(2, 4) << endl;

	cout <<  endl << "Comparators" << endl;
	// cout << "True is: " << true << endl;
	// cout << "False is: " << false << endl;
	cout << "2 < 40: " << MathFuncs::lssthan(nival2, nival40)->val << endl;
	cout << "2 > 40: " << MathFuncs::gtrthan(nival2, nival40)->val << endl;
	cout << "40 > 2: " << MathFuncs::gtrthan(nival40, nival2)->val << endl;
	cout << "\"40\" < 2: " << MathFuncs::lssthan(sval40, nival2)->val << endl;
	cout << "\"40\" > 2: " << MathFuncs::gtrthan(sval40, nival2)->val << endl;
    cout << "\"0\" < 2: " << MathFuncs::lssthan(sval0, nival2)->val << endl;
	cout << "2 == 2: " << MathFuncs::equalto(nival2, nival2)->val << endl;
	cout << "2 != 40: " << MathFuncs::neqto(nival2, nival40)->val << endl;
	cout << "2.1 < 2.2: " << MathFuncs::lssthan(nfval2one, nfval2two)->val << endl;

	printf("\nEND\n");

}
