#ifndef _ITERATION
#define _ITERATION 


#include "Node.h"


class IterationStatement : public Statement {
public:
    const Statement* stmt;
    IterationStatement(const Statement* s) : stmt(s) 
    {}
    void generateCode() const {
	}
};

class DoWhileIterationStatement : public IterationStatement {
public:
    const Expression* expr;
    DoWhileIterationStatement(const Statement* stmt, const Expression* e)
	: IterationStatement(stmt), expr(e)
    {}	
    void print(unsigned int tabs) const {
	indent(tabs); 
	cout << "do" << endl;
        stmt->print(tabs+1);
	indent(tabs);
	cout << " while ( ";
	expr->print(tabs);
	cout << " );";
    }
};

class WhileIterationStatement : public IterationStatement {
public:
    const Expression* expr;
    WhileIterationStatement(const Expression* e, const Statement* stmt)
	: IterationStatement(stmt), expr(e) 
    {}
    void print(unsigned int tabs) const {
	indent(tabs); 
	cout << " while ( ";
	expr->print(tabs);
	cout << " ) " << endl;
	stmt->print(tabs+1);
    }
};

#define cprint(p,x) { if(p!=NULL) p->print(x); }

class ForIterationStatement : public IterationStatement {
public:
    const Expression* refexpr;
    const Expression* testexpr;
    const Expression* incexpr;
    ForIterationStatement(const Expression* init, const Expression* test, const Expression* inc, const Statement* stmt)
	: IterationStatement(stmt), refexpr(init), testexpr(test), incexpr(inc)
    {}
    void print(unsigned int tabs) const {
	indent(tabs); 
	cout << "for ( ";
	cprint(refexpr,tabs);
	cout << " ; ";
	cprint(testexpr,tabs);
	cout << " ; ";
	cprint(incexpr,tabs)
	cout << " ) " << endl;
	stmt->print(tabs+1);
    }
};

class ForVarIterationStatement : public IterationStatement {
public:
    VariableDecList* vars;
    const Expression* testexpr;
    const Expression* incexpr;
    ForVarIterationStatement(VariableDecList* v, const Expression* test, const Expression* inc, const Statement* stmt)
	: IterationStatement(stmt), vars(v), testexpr(test), incexpr(inc) 
    {}
    void print(unsigned int tabs) const {
	indent(tabs); 
	cout << "for ( vars ";
	vars->print(tabs);
	cout << " ; ";
	cprint(testexpr,tabs);
	cout << " ; ";
	cprint(incexpr,tabs)
	cout << " ) " << endl;
	stmt->print(tabs+1);
    }
};

class ForInIterationStatement : public IterationStatement {
public:
    const Expression* left;
    const Expression* expr;
    ForInIterationStatement(const Expression* l, const Expression* e, const Statement* stmt)
	: IterationStatement(stmt), left(l), expr(e) 
    {}
    void print(unsigned int tabs) const {
	indent(tabs); 
	cout << "for ( ";
	left->print(tabs);
	cout << " in ";
	expr->print(tabs);
	cout << " )" << endl;
	stmt->print(tabs+1);
    }
};

class ForVarInIterationStatement : public IterationStatement {
public:
    const VariableDec* var;
    const Expression* expr;
    ForVarInIterationStatement(const VariableDec* v, const Expression* e, const Statement* stmt)
	: IterationStatement(stmt), var(v), expr(e) 
    {}
    void print(unsigned int tabs) const {
	indent(tabs); 
	cout << "for ( var ";
	var->print(tabs);
	cout << " in ";
	expr->print(tabs);
	cout << " )" << endl;
	stmt->print(tabs+1);
    }
};



#endif








