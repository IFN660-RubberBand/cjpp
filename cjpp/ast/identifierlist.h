#ifndef IDENTIFIERLIST
#define IDENTIFIERLIST

#include "Node.h"

class IdentifierList : public Node {
public:
    list<const Identifier*>* ident;	
    IdentifierList(const Identifier* i)
    {
         ident = new list<const Identifier*>();
	 append(i);	
    }
    IdentifierList()
    {
         ident = new list<const Identifier*>();
    }	
    ~IdentifierList() {
       	while(!ident->empty()) {
			delete ident->front(); 
			ident->pop_front();
		}
		delete ident;
	}
    void append(const Identifier* s) 
    {
	 ident->push_back(s);
    }
    void print(unsigned int tabs) const {
        for(list<const Identifier*>::iterator iter = ident->begin();
    	    iter != ident->end();
            iter++)
		{
        	(*iter)->print(tabs);  
        }	
    }
    void generateCode() const {
        	
    }
		
};

#endif
