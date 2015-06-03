#ifndef SOURCEELEMENTLIST
#define SOURCEELEMENTLIST

#include "Node.h"
#include "statement.h"


class SourceElementList : public Node {
public:
    list<const SourceElement*>* stmts;	
    SourceElementList(const SourceElement* s)
    {
        stmts = new list<const SourceElement*>();
	 	append(s);	
    }
    SourceElementList()
    {
         stmts = new list<const SourceElement*>();
    }	
    ~SourceElementList() {
       	while(!stmts->empty()) {
			delete stmts->front(); 
			stmts->pop_front();
		}
		delete stmts;
	}
    void append(const SourceElement* s) 
    {
	 stmts->push_back(s);
    }
    void print(unsigned int tabs) const {
        for(list<const SourceElement*>::iterator iter = stmts->begin();
    	    iter != stmts->end();
            iter++)
		{
        	(*iter)->print(tabs);  
        }	
    }
    
	void generateCode() const {
        for(auto iter = stmts->begin(); iter != stmts->end(); iter++)
		{
        	if((*iter)->isStatement()) {
        		(*iter)->generateCode(); 
			}
			 
        }	
    }
    
    void generateFunctions() {
    	for(auto iter = stmts->begin(); iter != stmts->end(); iter++)
		{
        	if((*iter)->isFunction()) {
        		((*iter))->generateFunctions(); 
			}
        }
	}
		
};

#endif
