#ifndef SCOPE
#define SCOPE

#include <map>
#include "value.h"
using namespace std;


class Scope {
private:
	Scope* prev;
public:
	map<string, Value*>* m;
	Scope() {
		prev = NULL;
		m = new map<string, Value*>();
	}
	
	Scope(Scope* prev) : prev(prev)	{
		m = new map<string, Value*>();
	}
	
	~Scope() {
		delete m;
	}
	
	
	Value* resolve(string ident) {
		auto search = m->find(ident);
    	if(search != m->end()) {
        	return search->second;
    	} else {
    		if(prev != NULL) {
				return prev->resolve(ident);
			} else {
				Value* value = new UndefinedValue();
        		//? (*m)[ident] = value;
        		return value;
			} 
				
    	}
	}

	Value* set(string ident, Value* value) {
		auto search = m->find(ident);
    	if(search != m->end()) {
			if(search->second != value) {
				delete search->second;
			}
			
		}
        (*m)[ident] = value;
        return value;
	}
	
	
	Scope* openScope() {
		Scope* new_scope = new Scope(this);
		return new_scope;
	}
	
	Scope* closeScope() {
		for (auto it = m->begin(); it != m->end(); ++it)
    		delete it->second;
		return prev;
	}
	
};






#endif
