#include "Node.h"

class UnaryExpression : public Expression {
public:
	const UnaryExpression* unexpr;
	UnaryExpression(const UnaryExpression* u)
	: unexpr(u)
	{}
};