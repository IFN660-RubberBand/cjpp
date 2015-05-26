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
	}
	bool generateCode() const {

	}
};

#endif
