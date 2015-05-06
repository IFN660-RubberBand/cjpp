#ifndef _WITH
#define _WITH

#include "Node.h"


class WithStatement  : public Statement {
public:
	const Statement* withstmt;
	const Expression* expr;
	WithStatement (const Statement* with, const Expression* expr)
	:withstmt(with), expr(expr);
	{}
	}
	
void print(unsigned int tabs) const {
    	indent(tabs); 
		cout << "with(" << endl;
		expr->print(tabs);
		cout << ")" << endl;
		withstmt -> print(tabs+1);
    }
		void generateCode() const {
	}
};

#endif
