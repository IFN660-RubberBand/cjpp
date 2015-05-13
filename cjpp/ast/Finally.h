#include "Node.h"
#include "block.h"

class FinallyStatement : public Statement{
public:
	Block* block;
	FinallyStatement(Block* b)
	 : block(b)
	{}
};
