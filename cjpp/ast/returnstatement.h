#ifndef RETEXPR
#define RETEXPR

#include "Node.h"

class ReturnStatement : public Statement {
public:
	const Expression* expr;
	ReturnStatement(const Expression* expr)
	: expr(expr)
	{}
	~ReturnStatement() {
		if(expr != NULL)
			delete expr;
	}
	void print(unsigned int tabs) const {
		indent(tabs);
		cout << "return ";
		expr->print(tabs);
		cout << endl;
	}

	void generateCode() const {
		TempVariable* t = TempVariableFactory::getTemp();
		expr->generateCode(t); 
		cout << "currentscope->closeScope();" << endl;
		cout << "delete currentscope;" << endl;
		cout << "return " << t->toString() << ";" << endl;
		delete t;
	}
};

#endif
