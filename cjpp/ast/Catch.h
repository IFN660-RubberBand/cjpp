#include "Node.h"
#include "block.h"

class CatchStatement : public Statement{
public:
	Block* block;
	const Identifier* identifier;
	CatchStatement(Block* b, const Identifier* i)
	 : identifier(i), block(b)
	{}
};
