#include "Node.h"

class NIfStatement : public NStatement {
public:
	NExpression* expr;
	NIfStatement(const NExpression* e, const NStatement* ifstmt, const NStatement* elsestmt)
	: NStatement(ifstmt), NStatement(elsestmt), expr(e)
	{}
};