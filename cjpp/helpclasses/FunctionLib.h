#include <stdio.h>
#include <string>
#include "value.h"
#include <iostream>
#include "Scope.h"
#include "functionvalue.h"
#include "value.h"

using namespace std;

class FunctionLib{
public: 
	static Value* call(Scope* currentscope, Value* function, list<Value*>* args){
		if (function->returnType() != 7)
		{
			cout << "TypeError: not a function!" << endl;
			return new UndefinedValue();
		}
		else 
		{
			return ((FunctionValue*)function)->ptr(currentscope, args);
		}
	}
};
