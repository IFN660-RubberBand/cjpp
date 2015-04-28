#include "Node.h"

class TryStatement_node : public Statement_node{
public:
  NExpression* expr;
	NTryStatement(const NExpression* e,const NStatement* try, const NStatement* catch, const NStatement* finally, const NStatement* block)
    : NStatement (try), NStatement(block), NStatement (catch), NStatemnt (finally)
	{}
};




