#include "Node.h"

class ReturnStatement : public Statement{
public:
const Expression* expr;
	ReturnStatement(const Expression* e, const Statement* return)
	: Statement(return), expr(e)
	{}

};
