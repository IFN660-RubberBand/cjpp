#ifndef _LABELLED
#define _LABELLED

#include "Node.h"


class LabelledStatement  : public Statement {
public:
	const Statement* labelledstmt;
	const Identifier* id;
	LabelledStatement (const Statement* labelled, const Identifier* i)
	:labelledstmt(labelled), id(i);
	{}
	}
	
void print(unsigned int tabs) const {
    	indent(tabs); 
		cout << "identifier" << endl;
		id ->print(tabs);
		cout <<"statement" << endl;
		labelledstmt->print(tabs+1);
    }
		void generateCode() const {
	}
};

#endif
