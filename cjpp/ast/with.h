#include "Node.h"

class WithStatement : public Statement{
public:
	const Expression* expr;
	WithStatement ( const Expression* e, const Expression* withstmt)
	: Statement(withstmt)
	{}
};
