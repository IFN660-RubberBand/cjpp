#include <iostream>
#include <list>
#include "Node.h"

#ifndef STATEMENTLIST
#define STATEMENTLIST

class StatementList : public Node {
public:
    std::list<const Statement*>* stmts;	
    StatementList(const Statement* s)
    {
         stmts = new std::list<const Statement*>();
	 append(s);	
    }
    StatementList()
    {
         stmts = new std::list<const Statement*>();
    }	
    void append(const Statement* s) 
    {
	 stmts->push_back(s);
    }
};




#endif
