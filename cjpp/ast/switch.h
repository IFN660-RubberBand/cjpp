#include "Node.h"
#include "Caseblock.h"

class SwitchStatement : public Statement {
public:
	const Expression* expr;
	Caseblock* cb;
	SwitchStatement(const Expression* e, const Statement* switch, Caseblock* c)
	: expr(e),cb(c);
	{}
};


