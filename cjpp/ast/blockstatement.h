
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
		unsigned int indention;
		indention = (tabs == 0) ? 0 : tabs-1;
		
		if(tabs == 0)
			++tabs;
		
		
		indent(indention); 
		cout << "{" << endl;
		if(l != NULL) 
			l->print(tabs);
		indent(indention); 
		cout << "}" << endl;
    }
    void generateCode() const {
    	if(l != NULL)
    		l->generateCode();
	}
};

#endif
