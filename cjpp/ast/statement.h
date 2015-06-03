#ifndef _STATEMENT
#define _STATEMENT

#include "Node.h"

class Statement : public SourceElement {
public:
	virtual void generateCode() const {
		cout << "statement not implemented yet" << endl;
	}
	
	bool isStatement() const{
		return true;
	}
	
	bool isFunction() const {
		return false;
	}
	
	void generateFunctions() const
	{}
};

#endif
