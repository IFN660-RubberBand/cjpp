#ifndef _CONTINUE
#define _CONTINUE

#include "Node.h"

class ContinueStatement : public Statement {
public:
	const Statement* continuestmt;
	const Identifier* id;
	ContinueStatement(const Statement* cont, const Identifier* i)
	:continuestmt(cont), id(i);
	{}
	}
	
void print(unsigned int tabs) const {
    	indent(tabs); 
		cout << "continue" << endl;
		id ->print(tabs);
    }
		void generateCode() const {
	}
};
