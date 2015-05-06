#ifndef _IF
#define _IF

#include "Node.h"

class IfStatement : public Statement {
public:
	const Statement* ifstmt;
	const Statement* elsestmt;
	const Expression* expr;
	IfStatement(const Expression* expr, Statement* ifs, Statement* elses)
	: expr(expr), ifstmt(ifs), elsestmt(elses) 
	{}
	~IfStatement() {
		delete expr;
		delete ifstmt;
		if(elsestmt != NULL)
			delete elsestmt;
	}
	void print(unsigned int tabs) const{
		indent(tabs);
		cout << "if (" << endl;
		expr->print(tabs);
		cout << ")" << endl;
		ifstmt->print(tabs+1);
		if (elsestmt != NULL) {
			cout << "else" << endl;
			elsestmt->print(tabs+1);
		}
	}
	void generateCode() const {
	}
};

#endif
