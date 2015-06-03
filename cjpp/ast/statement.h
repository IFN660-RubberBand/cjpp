#ifndef _STATEMENT
#define _STATEMENT

#include "Node.h"

class Statement : public Node {
public:
	virtual void generateCode() const {
		cout << "statement not implemented yet" << endl;
	}
};

#endif
