#ifndef CALLEXPRESSION
#define CALLEXPRESSION

#include "Node.h"

class CallExpression : public Expression {
public:
	const Expression* mexpr;
	const Expression* args;
	CallExpression(const Expression* mexpr, const Expression* args)
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
		TempVariable* t2 = TempVariableFactory::getTemp();

		bool del0 = mexpr->generateCode(t1);
		if(args != NULL)
			bool del1 = args->generateCode(t2);

		cout << result->toString() << " = FuncLib::call("<< t1->toString() << ", " << t2->toString() << ");" << endl;

		delete t1;
		delete t2;
	}
};

#endif
