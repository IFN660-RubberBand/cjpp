#include "Node.h"
#include "StatementList.h"

class CaseclauseStatement : public Statement {
public:
	StatementList* stmts;
	const Expression* expr;
	CaseclauseStatement(const Expression* e, StatementList* s)
	:expr(e), stmts(s) 
	{}
	
};
