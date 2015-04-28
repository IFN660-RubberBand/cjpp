#include "ast.h"

class ThrowStatement_node : public Statement_node{
public:
NExpression* expr;
	NThrowStatement(const NExpression* e, const NStatement* throw)
	: NStatement(throw), expr(e)
	{}

};
