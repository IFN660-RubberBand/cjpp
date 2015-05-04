#ifndef _EXPRESSION
#define _EXPRESSION

#include "Node.h"
#include "statement.h"

class ExpressionStatement : public Statement {
public:
    const Expression* expr;
    ExpressionStatement(const Expression* expr) : expr(expr)
    {}
    void print(unsigned int tabs) const {
        indent(tabs); 
		expr->print(tabs);
		cout << ";" << endl;
    }
    void generateCode() const {
    	expr->generateCode();
    	cout << ";" << endl;
	}
	
};

#endif
