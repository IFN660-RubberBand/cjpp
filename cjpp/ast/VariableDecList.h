#include "Node.h"
#include <list>
#include "VariableDec.h"

#ifndef VARIABLEDECLIST
#define VARIABLEDECLIST




class VariableDecList : public Node {
public:
    std::list<const VariableDec*>* stmts;	
    VariableDecList(const VariableDec* v)
    {
         stmts = new std::list<const VariableDec*>();
	 append(v);	
    }
    VariableDecList()
    {
         stmts = new std::list<const VariableDec*>();
    }	
    void append(const VariableDec* s)
    {
	 stmts->push_back(s);
    }
};

#endif
