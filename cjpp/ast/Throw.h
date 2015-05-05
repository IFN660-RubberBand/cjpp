#include "Node.h"

class ThrowStatement : public Statement {
public:
	const Expression* expr;
	ThrowStatement(const Expression* e)
	: expr(e)
	{}
};
