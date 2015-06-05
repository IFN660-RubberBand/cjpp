#ifndef FUNCVALUE
#define FUNCVALUE


#include "value.h"
#include "Scope.h"

class FunctionValue: public Value {
public:
	Value* (*ptr) (Scope*, list<Value*>*);
	
	FunctionValue(Value* (*ptr) (Scope*, list<Value*>*))	: ptr(ptr) {}
	
	bool toBoolean() {
    	return true;
	}
    float toFloat() {
        return NAN;
    }
    string toString() {
        return "Function";
    }
	Value* copy() {
		return new FunctionValue(ptr);
	}
	
	DataType returnType() {
		return Value::FunctionType;
	}
};

#endif