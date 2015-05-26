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
    			//cout << "tmp" << result << " = new IntegerValue(" << tmp0 << "->v + " << tmp1 << "->v);" << endl; 
    			//cout << " " << *t1;
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
    			
    		case DIVIDE:
    			cout << result->toString() << " = new IntegerValue(" << t1->toString() << "->v / " << t2->toString() << "->v);" << endl;
    			//cout << "tmp" << result << " = libcjpp_div(" << tmp0 << ", " << tmp1 << ");" << endl;
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
		TempVariable* t1 = TempVariableFactory::getTemp();
		JumpLabel* l = JumpLabelFactory::getLabel();		
		//generate normal code for the left operand		
    	bool del0 = left->generateCode(t1);
    	
    	
    	
    	if(del0)
    		cout << result->toString() << " = " << t1->toString() << ";" << endl;
    	else	//copy the result into the result correcr variable
			cout << result->toString() << " = " << t1->toString() << "->copy();" << endl;
    	
    		
		if(op == OR)//if OR and TRUE jump to the end
			cout << "if(" << result->toString() << "->toBoolean()) " << "goto " << l->toString() << ";" << endl;
		else if(op == AND)//if AND and FALSE jump to the end
			cout << "if(!" << result->toString() << "->toBoolean()) " << "goto " << l->toString() << ";" << endl;
		
		//delete result, we need to overwrite it
		cout << "delete " << result->toString() << ";" << endl;
		
		//generate code for the right operand
		del0 = right->generateCode(t1);
		if(del0)
    		cout << result->toString() << " = " << t1->toString() << ";" << endl;
    	else	
			cout << result->toString() << " = " << t1->toString() << "->copy();" << endl;
		
		//jump label
		cout << l->toString() << ":" << endl;
		
		delete t1;
		delete l;
    	return true;	
	}
	
	
};


#endif
