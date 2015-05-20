
#ifndef _VARIABLE
#define _VARIABLE

#include "Node.h"
#include "statement.h"

class VariableStatement : public Statement {
public:
    VariableDecList* l;
    VariableStatement(VariableDecList* l) : l(l)
    {}
    ~VariableStatement() {
    	delete l;
	}
    void print(unsigned int tabs) const {
        indent(tabs); 
		cout << "var ";
		l->print(tabs);
		cout << ";" << endl;
    }
    void generateCode() const {
	
    	TempVariable* t = TempVariableFactory::getTemp();
	

	l->generateCode(t);

	delete t;
	}
};

#endif
