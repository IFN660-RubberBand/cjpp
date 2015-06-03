#ifndef BINARYEXPR
#define BINARYEXPR


#include "Node.h"
#include "../cjpp.tab.h"
#include "../helpclasses/TempVariable.h"
#include "../helpclasses/TempVariableFactory.h"
#include "../helpclasses/JumpLabelFactory.h"
#include "../helpclasses/JumpLabel.h"

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
    	if(op == AND || op == OR) {
    		return generateLazyCode(result);
		}	
    		
    		
		TempVariable* t1 = TempVariableFactory::getTemp();
		TempVariable* t2 = TempVariableFactory::getTemp();
		
				
    	bool del0 = left->generateCode(t1);
    	bool del1 = right->generateCode(t2);
		
		
		switch(op) {
    		case PLUS:
    			cout << result->toString() << " = MathFuncs::addV2(" << t1->toString() << ", " << t2->toString() << ");" << endl; 
    			break;
    
			case MINUS:
				cout << result->toString() << " = MathFuncs::sub(" << t1->toString() << ", " << t2->toString() << ");" << endl; 
				break;	
    		
    		case MULTIPLY:
    			cout << result->toString() << " = MathFuncs::mul(" << t1->toString() << ", " << t2->toString() << ");" << endl; 
    			break;
    			
    		case DIVIDE:
    			cout << result->toString() << " = MathFuncs::div(" << t1->toString() << ", " << t2->toString() << ");" << endl;
    			break;

    		case GTR:
                cout << result->toString() << " = MathFuncs::gtrthan(" << t1->toString() << ", " << t2->toString() << ");" << endl;
                break;

    		case LSS:
                cout << result->toString() << " = MathFuncs::lssthan(" << t1->toString() << ", " << t2->toString() << ");" << endl;
                break;

    		case LEQ:
                cout << result->toString() << " = MathFuncs::leqthan(" << t1->toString() << ", " << t2->toString() << ");" << endl;
                break;
                       
    		case GEQ:
                cout << result->toString() << " = MathFuncs::geqthan(" << t1->toString() << ", " << t2->toString() << ");" << endl;
                break;
                       
    		case EQUAL:
                cout << result->toString() << " = MathFuncs::equalto(" << t1->toString() << ", " << t2->toString() << ");" << endl;
                break;
                       
    		case NEQ:
                cout << result->toString() << " = MathFuncs::neqto(" << t1->toString() << ", " << t2->toString() << ");" << endl;
                break;
                       
            case NIDENT:
                cout << result->toString() << " = MathFuncs::nidentto(" << t1->toString() << ", " << t2->toString() << ");" << endl;
                break;
                       
            case IDENT:
    			cout << result->toString() << " = MathFuncs::identto(" << t1->toString() << ", " << t2->toString() << ");" << endl;
    			break;			
				
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
	
	bool generateLazyCode(TempVariable* result) const {
		JumpLabel* l = JumpLabelFactory::getLabel();		
		//generate normal code for the left operand		
    	bool free = left->generateCode(result);
    	
    	
    	
    	if(!free)
			cout << result->toString() << " = " << result->toString() << "->copy();" << endl;
    		//copy the result into the result correct variable
			
    	
    		
		if(op == OR)//if OR and TRUE jump to the end
			cout << "if(" << result->toString() << "->toBoolean()) " << "goto " << l->toString() << ";" << endl;
		else if(op == AND)//if AND and FALSE jump to the end
			cout << "if(!" << result->toString() << "->toBoolean()) " << "goto " << l->toString() << ";" << endl;
		
		//delete result, we need to overwrite it
		cout << "delete " << result->toString() << ";" << endl;
		
		//generate code for the right operand
		free = right->generateCode(result);
		if(!free)
			cout << result->toString() << " = " << result->toString() << "->copy();" << endl;
    		//copy the result into the result correct variable
		
		//jump label
		cout << l->toString() << ":" << endl;
		
		delete l;
    	return true;	
	}
	
	
};


#endif
