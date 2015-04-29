#include "Node.h"
#include "Defaultclause.h"
#include "Caseclauses.h"

class CaseblockStatement : public Statement {
public:
	Defaultclause defaultclause;
	Caseclauses caseclauses;
	Caseblock(Defaultclause dc, Caseclauses cc)
	: Caseclauses(cc), Defaultclause(dc)
	{}
	
};
