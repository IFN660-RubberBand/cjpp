#include "Node.h"

class NSwitchStatement : public NStatement {
public:
	NExpression* expr;
	NSwitchStatement(const NExpression* e, const NStatement* switch, const NStatement* caseblock)
	: NStatement(switch), nStatement(caseblock), expr(e)
	{}
};

class NCaseblockStatement : public NStatement {
public:
	NCaseblock(const NStatement* defaultclause, const NStatement* caseclause)
	: NStatement(caseclause), NStatement(defaultclause)
	{}
	
};

class NCaseclausesStatement : public NStatement {
public:
	NCaseclauses(const NStatement* caseclauses, const NStatement* caseclause)
	: NStatement(caseclauses), NStatement(caseclause)
	{}
	
};

class NCaseclauseStatement : public NStatement {
public:
	NCaseclause(const NExpression* e, const NStatement* caseclause, const NStatement* stmtlist)
	: NStatement(caseclause), NStatement(stmtlist), expr(e)
	{}
	
};

class NDefaultclauseStatement : public NStatement {
public:
	NDefaultclause(const NStatement* default, const NStatement* stmtlist)
	: NStatement(default), NStatement(stmtlist),
	{}
	
};

