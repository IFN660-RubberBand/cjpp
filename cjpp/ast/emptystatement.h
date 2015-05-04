#ifndef _EMPTY
#define _EMPTY

#include "statement.h"

class EmptyStatement : public Statement {
public:
    void print(unsigned int tabs) const {
    	indent(tabs); 
		cout << ";" << endl;
    }
	void generateCode() const {
    	cout << ";" << endl;
	}
};


#endif
