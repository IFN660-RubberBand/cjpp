#include <stdio.h>
#include <string>
#include "value.h"
#include <iostream>

using namespace std;

class FunctionLib{
public: 
	static Value* call(Value* function, list<Value*>* args){
		if (function->returnType() != 7)
		{
			cout << "TypeError: " << function->toString() << " is not a function!" << endl;
			return new UndefinedValue();
		}
		else 
		{
			return ((FunctionValue*)function)->ptr(args);
		}
	}
};