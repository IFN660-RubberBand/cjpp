#include <stdint.h>
#include <map>
#include <stdio.h>
#include <string>
#include <iostream>

#ifndef VALUE
#define VALUE

using namespace std;



class Value {

};

class UndefinedValue : public Value {
};

class IntegerValue : public Value {
public:
	int32_t v;
	IntegerValue(int32_t v) : v(v)
	{}
};

class ObjectValue : public Value {
public:
	map<char*, Value*>* m;
	ObjectValue() {
		m = new map<char*, Value*>();
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
		auto search = m->find(ident);
    	if(search != m->end()) {
			cout << "delete old object" << endl;	
			//delete search->second;
		}
        (*m)[ident] = value;
	}
	
};




#endif
