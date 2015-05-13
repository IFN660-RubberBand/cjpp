#include <stdint.h>
#include <map>
#include <stdio.h>
#include <string>
#include <iostream>

#ifndef VALUE
#define VALUE

using namespace std;



class Value {
	virtual int returnType() = 0;
};

class UndefinedValue : public Value {
};

class IntegerValue : public Value {
public:
	int32_t v;
	IntegerValue(int32_t v) : v(v)
	{}
	int returnType() return 1;
};

class ObjectValue : public Value {
public:
	map<char*, Value*>* m;
	ObjectValue() {
		m = new map<char*, Value*>();
	}
	int returnType() return 0;
	Value* resolve(char* ident) {
		auto search = m->find(ident);
    	if(search != m->end()) {
        	return search->second;
    	} else {
			Value* value = new UndefinedValue();
        	//? (*m)[ident] = value;
        	return value;
    	}
	}

	void set(char* ident, Value* value) {
		auto search = m->find(ident);
    	if(search != m->end()) {
			cout << "delete old object" << endl;	
			//delete search->second;
		}
        (*m)[ident] = value;
	}
	
};

class FloatValue : public Value {
	float v;
	FloatValue(float v) : v(v) {}
	int returnType() return 5;
};

class StringValue : public Value {
public:
	char* v;
	IntegerValue(char* v) : v(v)
	{}
	int returnType() return 3;
};

class BooleanValue : public Value {
public:
	bool v;
	IntegerValue(bool v) : v(v)
	{}
	int returnType() return 4;
};



#endif
