#ifndef CALLEXPRESSION
#define CALLEXPRESSION

#include "Node.h"

class CallExpression : public Expression {
public:
	const Identifier* ident;
	const Expression* args;
	CallExpression(const Identifier* ident, const Expression* args)
	: ident(ident), args(args)
	{}
	~CallExpression() {
		delete ident;
		delete args;
	}
	void print(unsigned int tabs) const {
		Expression::print(tabs);
		cout << "function call ";
		ident->print(tabs);
		cout << "(";
		args->print(tabs);
		cout << ")";
	}

	bool generateCode(TempVariable* result) const {
		TempVariable* t = TempVariableFactory::getTemp();
		bool del0 = args->generateCode(t);

		string logfunc = "console.log";
		string name = ident->toString();

		if (logfunc == name) {
			cout << "cout << " << t->toString() << " << endl;" << endl;
		}
		else {
			cout << "currentscope->resolve(\"" << ident->toString() << "\", " << t->toString() << ")" << endl; 
		}
		
	}
};

#endif
