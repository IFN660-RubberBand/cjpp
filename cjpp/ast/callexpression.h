#ifndef CALLEXPRESSION
#define CALLEXPRESSION

#include "Node.h"
#include "expressionlist.h"

class CallExpression : public Expression {
public:
	const Expression* mexpr;
	ExpressionList* args;
	CallExpression(const Expression* mexpr, ExpressionList* args)
	: mexpr(mexpr), args(args)
	{}
	~CallExpression() {
		delete mexpr;
		delete args;
	}

	void print(unsigned int tabs) const {
		Expression::print(tabs);
		cout << "function call ";
		mexpr->print(tabs);
		cout << "(";
		if(args != NULL)
			args->print(tabs);
		cout << ")";
	}

bool generateCode(TempVariable* result) const {
		TempVariable* t1 = TempVariableFactory::getTemp();
		TempVariable* t2;

		bool del[args == NULL? 0 : args->exprs->size()];
		int i = 0;
		
		if(args != NULL) {
			cout << "list<Value*>* l = new list<Value*>();" << endl;
			t2 = TempVariableFactory::getTemp();
			
			for(auto iter = args->exprs->begin(); iter != args->exprs->end(); iter++)
			{	
        		del[i++] = (*iter)->generateCode(t2);
				if(del)
					cout << "l->push_back(" << t2->toString() << ");" << endl;
				else 
					 cout << "l->push_back(" << t2->toString() << "->copy());" << endl;
        	}
        	
        	
			delete t2;
		}
		
		bool del0 = mexpr->generateRightHandCode(t1);
				
		if(args != NULL)
			cout << result->toString() << " = FunctionLib::call(currentscope, " << t1->toString() << ", " << "l);" << endl;
		else 
			cout << result->toString() << " = FunctionLib::call(currentscope, " << t1->toString() << ", " << "NULL);" << endl;
		
		if(args != NULL) {
			cout << "delete l;" << endl;
		}
			
			
		delete t1;
		return true;
}

};

#endif
