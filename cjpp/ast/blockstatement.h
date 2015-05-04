
#ifndef _BLOCK
#define _BLOCK


#include "Node.h"
#include "statementlist.h"

class Block : public Statement {
public:
    StatementList* l;
    Block(StatementList* l) : l(l)
    {}
    ~Block() {
    	delete l;
	}
    void print(unsigned int tabs) const {
		indent(tabs-1); 
		cout << "{" << endl;
		if(l != NULL) 
			l->print(tabs);
		indent(tabs-1); 
		cout << "}" << endl;
    }
    void generateCode() const {
    	cout << "{" << endl;
    	l->generateCode();
    	cout << "}" << endl;
	}
};

#endif
