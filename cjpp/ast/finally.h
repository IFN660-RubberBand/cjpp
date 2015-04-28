#include "Node.h"

class NFinallyStatement : public Statement_node{
public:
	NFinallyStatement(const NStatement* finally, const Nstatemnt* block)
	:NStatement (finally), NStatement(block)
	{}
	
};
