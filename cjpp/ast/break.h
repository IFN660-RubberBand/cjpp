#include "Node.h"

class NBreakStatement : public NStatement {

public:

	NIdentifier* id;

	NBreakStatement(const NIdentifier* i, const NStatement* break)

	: NStatement(break), id(i)

	{}

};
