#include "Node.h"

class NWithStatement : public Statement_node{
public:
	NExpression* expr;
	NWithStatement ( const NExpression* e, const NExpression* withstmt)
	: NStatement(withstmt)
	{}
};
