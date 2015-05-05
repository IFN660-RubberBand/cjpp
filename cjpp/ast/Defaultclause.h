#include "Node.h"
#include "StatementList.h"

class DefaultclauseStatement : public Statement {
public:
	StatementList* stmts;
	DefaultclauseStatement( StatementList* s)
	:stmts(s) 
	{}
	
};
