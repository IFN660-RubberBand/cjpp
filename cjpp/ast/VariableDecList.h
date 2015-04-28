#include "Node.h"


class VariableDecList : public Node {
public:
    list<const VariableDec*>* stmts;	
    VariableDecList(const VariableDec* v)
    {
         stmts = new list<const VariableDec*>();
	 append(v);	
    }
    VariableDecList()
    {
         stmts = new list<const VariableDec*>();
    }	
    void append(const VariableDec* s)
    {
	 stmts->push_back(s);
    }
};

