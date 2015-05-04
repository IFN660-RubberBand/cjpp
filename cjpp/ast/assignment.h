
#ifndef ASSIGNMENT
#define ASSIGNMENT
#include "Node.h"


class AssignmentExpression : public Expression {
public:
    const Expression* left;	
	int op;
    const Expression* expr;
    
    AssignmentExpression(const Expression* left, const Expression* expr)
	: left(left), expr(expr)
    {
        op = NULL;
    }
    AssignmentExpression(const Expression* left, int op, const Expression* expr)
	: left(left), op(op), expr(expr)
    {}
    ~AssignmentExpression() {
    	delete left;
    	delete expr;
	}
    void print(unsigned int tabs) const {
		Expression::print(tabs);
        left->print(tabs);
		if(op != NULL)
			cout << " " << (char) op << "= ";
		else
			cout << " = ";
		expr->print(tabs);
	}
	void generateCode() const {
		left->generateLeftHandCode();
		cout << " = ";
		expr->generateRightHandCode(); 
	}		
};

#endif
