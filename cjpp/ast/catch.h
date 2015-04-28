#include "Node.h"

class NCatchStatement : public Statement_node{
public:
	NIdentifier* id;
	NCatchStatement( const NIdentifier* i, const NStatement* catch)
	:NStatement (catch), id(i), NStatement(Block)
	{}
	
};
