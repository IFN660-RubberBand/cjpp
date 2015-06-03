
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
        op = 0;
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
		if(op != 0)
			cout << " " << (char) op << "= ";
		else
			cout << " = ";
		expr->print(tabs);
	}
	bool generateCode(TempVariable* result) const {
		cout << endl << "//Assignment" << endl;
		bool del = expr->generateCode(result);
		if(!del)
			cout << result->toString() << " = " << result->toString() << "->copy();" << endl; 
		if(op == 0) {
			left->generateLeftHandCode(result);
		} else {
			cout << "not implemented yet" << endl;
		}
		
		return false;
	}		
};

#endif
