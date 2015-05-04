#ifndef STATEMENTLIST
#define STATEMENTLIST

#include "Node.h"
#include "statement.h"

class StatementList : public Node {
public:
    list<const Statement*>* stmts;	
    StatementList(const Statement* s)
    {
         stmts = new list<const Statement*>();
	 append(s);	
    }
    StatementList()
    {
         stmts = new list<const Statement*>();
    }	
    void append(const Statement* s) 
    {
	 stmts->push_back(s);
    }
    void print(unsigned int tabs) const {
        for(list<const Statement*>::iterator iter = stmts->begin();
    	    iter != stmts->end();
            iter++)
		{
        	(*iter)->print(tabs);  
        }	
    }
    void generateCode() const {
        for(list<const Statement*>::iterator iter = stmts->begin();
    	    iter != stmts->end();
            iter++)
		{
        	(*iter)->generateCode();  
        }	
    }
		
};

#endif
