#ifndef BINARYEXPR
#define BINARYEXPR


#include "Node.h"
#include "../cjpp.tab.h"
#include "../helpclasses/TempVariableFactory.h"

class BinaryExpression : public Expression {

public:
    const Expression* left;	
	int op;
    const Expression* right;
    BinaryExpression(const Expression* left, int op, const Expression* right)
	: left(left), op(op), right(right)
    {}
    ~BinaryExpression() {
    	delete left;
    	delete right;
	}
    void print(unsigned int tabs) const {
		Expression::print(tabs);
        left->print(tabs);
		cout << " " << (char) op << " ";
		right->print(tabs);
    }	
    
    bool generateCode(TempVariable* result) const {
    		
		TempVariable* t1 = TempVariableFactory::getTemp();
		TempVariable* t2 = TempVariableFactory::getTemp();
		
				
    	bool del0 = left->generateCode(t1);
    	bool del1 = right->generateCode(t2);
		
		
		switch(op) {
    		case PLUS:
    			//cout << "tmp" << result << " = new IntegerValue(" << tmp0 << "->v + " << tmp1 << "->v);" << endl; 
    			cout << result->toString() << " = libcjpp_add(" << t1->toString() << ", " << t2->toString() << ");" << endl; 
    			break;
    
			case MINUS:
				//cout << "tmp" << result << " = new IntegerValue(" << tmp0 << "->v - " << tmp1 << "->v);" << endl; 
				cout << result->toString() << " = libcjpp_sub(" << t1->toString() << ", " << t2->toString() << ");" << endl; 
				break;	
    		
    		case MULTIPLY:
    			cout << result->toString() << " = new IntegerValue(" << t1->toString() << "->v * " << t2->toString() << "->v);" << endl; 
    			//cout << "tmp" << result << " = libcjpp_mult(" << tmp0 << ", " << tmp1 << ");" << endl; 
    			break;
    			
    			
    		//case DIVIDE:
			//	break;
				
				
			default:
				cout << "error: operation not implemented yet" << endl;			
		}
		if(del0)
			cout << "delete " << t1->toString() << ";" << endl;
    	if(del1)
			cout << "delete " << t2->toString() << ";" << endl;
		delete t1;
		delete t2;	
		return true;	
	}
};


#endif
