#ifndef _STATEMENT
#define _STATEMENT

#include "Node.h"

class Statement : public Node {
public:
	virtual void generateCode() const = 0;
};

#endif
