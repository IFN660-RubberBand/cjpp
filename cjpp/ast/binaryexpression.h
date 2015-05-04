
#ifndef BINARYEXPR
#define BINARYEXPR
#include "Node.h"

class BinaryExpression : public Expression {

public:
    const Expression* left;	
	int op;
    const Expression* right;
    BinaryExpression(const Expression* left, int op, const Expression* right)
	: left(left), op(op), right(right)
    {}
    void print(unsigned int tabs) const {
		Expression::print(tabs);
        left->print(tabs);
		cout << " " << (char) op << " ";
		right->print(tabs);
    }	
};


#endif
