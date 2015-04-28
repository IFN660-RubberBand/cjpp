#include "Node.h"

class TryStatement_node : public Statement_node{
public:
  NExpression* expr;
	NTryStatement(const NExpression* e,const NStatement* try, const NStatement* catch, const NStatement* finally, const NStatement* block)
    : NStatement (try), NStatement(block), NStatement (catch), NStatemnt (finally)
	{}
};

class NCatchStatement : public Statement_node{
public:
	NIdentifier* id;
	NCatchStatement( const NIdentifier* i, const NStatement* catch)
	:NStatement (catch), id(i), NStatement(Block)
	{}
	
};

class NFinallyStatement : public Statement_node{
public:
	NFinallyStatement(const NStatement* finally, const Nstatemnt* block)
	:NStatement (finally), NStatement(block)
	{}
	
};
