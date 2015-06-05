#include "Node.h"

#ifndef EXPRESSIONLIST
#define EXPRESSIONLIST


class ExpressionList : public Node {
public:
    list<const Expression*>* exprs;	
    ExpressionList(const Expression* s)
    {
        exprs = new list<const Expression*>();
	 	append(s);	
    }
    
    ExpressionList()
    {
         exprs = new list<const Expression*>();
    }	
    
    ~ExpressionList() {
       	while(!exprs->empty()) {
			delete exprs->front(); 
			exprs->pop_front();
		}
		delete exprs;
	}
	
    void append(const Expression* s) 
    {
	 exprs->push_back(s);
    }
    
    void print(unsigned int tabs) const {
        for(list<const Expression*>::iterator iter = exprs->begin();
    	    iter != exprs->end();
            iter++)
		{
        	(*iter)->print(tabs);  
        }	
    }
    
    void generateCode() const {

    }
		
};

#endif
