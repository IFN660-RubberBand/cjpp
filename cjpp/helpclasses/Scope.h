#ifndef SCOPE
#define SCOPE

#include "value.h"


class Scope {
private:
	Scope* prev;
public:
	map<char*, Value*>* m;
	Scope() {
		prev = NULL;
		m = new map<char*, Value*>();
	}
	
	Scope(Scope* prev) : prev(prev)	{
		m = new map<char*, Value*>();
	}
	
	~Scope() {
		delete m;
	}
	
	
	Value* resolve(char* ident) {
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

	void set(char* ident, Value* value) {
		auto search = m->find(ident);
    	if(search != m->end()) {
			cout << "delete old object" << endl;	
			//delete search->second;
		}
        (*m)[ident] = value;
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
