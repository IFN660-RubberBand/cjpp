#include "Node.h"
#include "Caseclause.h"

class CaseclausesStatement : public Statement {
public:
	Caseclause* caseclause;
	CaseclausesStatement(Caseclause* c)
	: Caseclauses(c), 
	{}
	
};
