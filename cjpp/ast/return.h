#ifndef _RETURN
#define _RETURN

#include "Node.h"


class ReturnStatement  : public Statement {
public:
	const Statement* return;
	const Expression* expr;
	ReturnStatement (const Statement* ret, const Expression* expr)
	:return(ret), expr(expr);
	{}
	}
	
void print(unsigned int tabs) const {
    	indent(tabs); 
		cout << "return" << endl;
		expr->print(tabs);
    }
		void generateCode() const {
	}
};

#endif
