#include "Node.h"
#include "StatementList.h"

class IfStatement : public Statement {
public:
	StatementList* stmts;
	const Expression* expr;
	IfStatement(const Expression* e, StatementList* s)
	: expr(e), stmts(s)
	{}
};