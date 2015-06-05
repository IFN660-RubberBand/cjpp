#ifndef UNARYEXPR
#define UNARYEXPR


#include "Node.h"
#include "../cjpp.tab.h"
#include "../helpclasses/TempVariable.h"
#include "../helpclasses/TempVariableFactory.h"
#include "../helpclasses/JumpLabelFactory.h"
#include "../helpclasses/JumpLabel.h"

class UnaryExpression : public Expression {
public:
    int op;
    const Expression* expr;
    UnaryExpression(int op, const Expression* expr)
	: op(op), expr(expr)
    {}
    ~UnaryExpression() {
    	delete expr;
	}
    void print(unsigned int tabs) const {
        Expression::print(tabs);
	cout << " " << (char) op << " ";
	expr->print(tabs);

    }	
    
    bool generateCode(TempVariable* result) const {
    	TempVariable* t1 = TempVariableFactory::getTemp();
		bool del = expr->generateCode(t1);
		
		if(op == PLUS) {
    		cout << result->toString() << " = MathFuncs::unaryPlus(" << t1->toString() << ");" << endl; 
		} else if(op == MINUS) {
			cout << result->toString() << " = MathFuncs::unaryMinus(" << t1->toString() << ");" << endl;
		}
		if(del)
			cout << "delete " << t1->toString() << ";";
		return true;
	}
};



#endif
