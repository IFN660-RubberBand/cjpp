#include <stdint.h>
#include <map>
#include <stdio.h>
#include <string>
#include <iostream>

#ifndef VALUE
#define VALUE

using namespace std;



class Value {
	virtual int getType() = 0;
};

class UndefinedValue : public Value {
	int getType() { return 0; } 
};

class IntegerValue : public Value {
public:
	int32_t v;
	IntegerValue(int32_t v) : v(v)
	{}
	int getType() { return 1; } 
};

class ObjectValue : public Value {
public:
	map<char*, Value*>* m;
	ObjectValue() {
		cout << "constructor";
		m = new map<char*, Value*>();
		(*m)["i"] = 42;
		auto search = m->find("i");
    	if(search != m->end()) {
        	cout << "found";
    	} else {
        	cout << "not found";
    	}
	}
	int getType() { return 2;
	}
	Value* resolve(char* ident) {
		auto search = m->find(ident);
    	if(search != m->end()) {
        	return search->second;
    	} else {
        	return new UndefinedValue();
    	}
	}
	void set(char* ident, Value* value) {
		//TODO delete old value of map[ident]
		(*m)[ident] = value;
	}	

	
};




#endif
