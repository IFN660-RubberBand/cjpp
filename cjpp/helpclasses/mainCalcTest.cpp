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

    cout << endl << "> Addtion (new addV2 method)" << endl;
    cout << "int + int: \t\t" << MathFuncs::addV2(nival40, nival2)->toString() << endl;
    cout << "float + float: \t\t" << MathFuncs::addV2(nfval40one, nfval40two)->toString() << endl;
    cout << "string + string: \t" << MathFuncs::addV2(sval40, sval2)->toString() << endl;
    cout << "int + string: \t\t" << MathFuncs::addV2(nival40, sval2)->toString() << endl;
    cout << "string + int: \t\t" << MathFuncs::addV2(sval2, nival40)->toString() << endl;
    cout << "float + string: \t" << MathFuncs::addV2(nfval40one, sval2)->toString() << endl;
    cout << "string + float: \t" << MathFuncs::addV2(sval2, nfval40one)->toString() << endl;

    cout << endl << "> Subtraction (new subV method)" << endl;
    cout << "int - int: \t\t" << MathFuncs::subV(nival40, nival2)->toString() << endl;
    cout << "float - float: \t\t" << MathFuncs::subV(nfval40one, nfval40two)->toString() << endl;
    cout << "string - string: \t" << MathFuncs::subV(svalHello, svalWorld)->toString() << endl;
    cout << "num s - num s: \t\t" << MathFuncs::subV(sval40, sval2)->toString() << endl;
    cout << "int - string: \t\t" << MathFuncs::subV(nival40, svalWorld)->toString() << endl;
    cout << "string - int: \t\t" << MathFuncs::subV(svalWorld, nival40)->toString() << endl;
    cout << "float - string: \t" << MathFuncs::subV(nfval40one, svalWorld)->toString() << endl;
    cout << "string - float: \t" << MathFuncs::subV(svalWorld, nfval40one)->toString() << endl;

    cout << endl << "> Multiplication" << endl;
    cout << "int * int: \t\t" << MathFuncs::multV(nival40, nival2)->toString() << endl;
    cout << "float * float: \t\t" << MathFuncs::multV(nfval40one, nfval40two)->toString() << endl;
    cout << "string * string: \t" << MathFuncs::multV(svalHello, svalWorld)->toString() << endl;
    cout << "num s * num s: \t\t" << MathFuncs::multV(sval40, sval2)->toString() << endl;
    cout << "int * string: \t\t" << MathFuncs::multV(nival40, svalWorld)->toString() << endl;
    cout << "string * int: \t\t" << MathFuncs::multV(svalWorld, nival40)->toString() << endl;
    cout << "float * string: \t" << MathFuncs::multV(nfval40one, svalWorld)->toString() << endl;
    cout << "string * float: \t" << MathFuncs::multV(svalWorld, nfval40one)->toString() << endl;

    cout << endl << "> Division" << endl;
    cout << "int / int: \t\t" << MathFuncs::divV(nival40, nival2)->toString() << endl;
    cout << "float / float: \t\t" << MathFuncs::divV(nfval40one, nfval40two)->toString() << endl;
    cout << "string / string: \t" << MathFuncs::divV(svalHello, svalWorld)->toString() << endl;
    cout << "num s / num s: \t\t" << MathFuncs::divV(sval40, sval2)->toString() << endl;
    cout << "int / string: \t\t" << MathFuncs::divV(nival40, svalWorld)->toString() << endl;
    cout << "string / int: \t\t" << MathFuncs::divV(svalWorld, nival40)->toString() << endl;
    cout << "float / string: \t" << MathFuncs::divV(nfval40one, svalWorld)->toString() << endl;
    cout << "string / float: \t" << MathFuncs::divV(svalWorld, nfval40one)->toString() << endl;

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
	cout << "2 < 40: " << MathFuncs::lssthan(nival2, nival40)->toBoolean() << endl;
	cout << "2 > 40: " << MathFuncs::gtrthan(nival2, nival40)->toBoolean() << endl;
	cout << "40 > 2: " << MathFuncs::gtrthan(nival40, nival2)->toBoolean() << endl;
	cout << "\"40\" < 2: " << MathFuncs::lssthan(sval40, nival2)->toBoolean() << endl;
	cout << "\"40\" > 2: " << MathFuncs::gtrthan(sval40, nival2)->toBoolean() << endl;
    cout << "\"0\" < 2: " << MathFuncs::lssthan(sval0, nival2)->toBoolean() << endl;
	cout << "2 == 2: " << MathFuncs::equalto(nival2, nival2)->toBoolean() << endl;
	cout << "2 != 40: " << MathFuncs::neqto(nival2, nival40)->toBoolean() << endl;
	cout << "2.1 < 2.2: " << MathFuncs::lssthan(nfval2one, nfval2two)->toBoolean() << endl;
    cout << "\"40\" === 40: " << MathFuncs::identto(sval40, nival40)->toBoolean() << endl;
    cout << "2 === 2: " << MathFuncs::identto(nival2, nival2)->toBoolean() << endl;
    cout << "\"40\" !== 40: " << MathFuncs::nidentto(sval40, nival40)->toBoolean() << endl;
    cout << "2 !== 2: " << MathFuncs::nidentto(nival2, nival2)->toBoolean() << endl;

	printf("\nEND\n");

}
