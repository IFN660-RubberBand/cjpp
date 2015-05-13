#include "Node.h"



class NContinueStatement : public NStatement {

public:

	NIdentifier* id;

	NContinueStatement(const NIdentifier* i, const NStatement* continue)

	: NStatement(continue), id(i)

	{}

};
