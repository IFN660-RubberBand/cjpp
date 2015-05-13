#include "Node.h"
#include "Catch.h"
#include "block.h"
#include "Finally.h"


class TryStatement : public Statement{
public:
	Catch* catch;
	Finally* finally;
	Block* block;
	TryStatement(Finally* f, Block* b, Catch* ca)
	 : catch(ca), finally(f), block(b)
	{}
};



