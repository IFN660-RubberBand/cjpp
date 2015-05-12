#ifndef _EXPRESSION
#define _EXPRESSION

#include "Node.h"
#include "statement.h"
#include "../helpclasses/TempVariableFactory.h"

class ExpressionStatement : public Statement {
public:
    const Expression* expr;
    ExpressionStatement(const Expression* expr) : expr(expr)
    {}
    ~ExpressionStatement() {
    	delete expr;
	}
    void print(unsigned int tabs) const {
        indent(tabs); 
		expr->print(tabs);
		cout << ";" << endl;
    }
    void generateCode() const {
    	TempVariableFactory::reset();
    	TempVariable* t = TempVariableFactory::getTemp();
		expr->generateCode(t);
		delete t;
	}
	
};

#endif
