#include "Node.h"

class ReturnStatement_node : public Statement_node{
public:
NExpression* expr;
	NReturnStatement(const NExpression* e, const NStatement* return)
	: NStatement(return), expr(e)
	{}

};
