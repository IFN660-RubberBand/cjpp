#include "Node.h"


class IterationStatement : public Statement {
public:
    const Statement* stmt;
    IterationStatement(const Statement* s) : stmt(s) 
    {}
};

class DoWhileIterationStatement : public IterationStatement {
public:
    const Expression* expr;
    DoWhileIterationStatement(const Statement* stmt, const Expression* e)
	: IterationStatement(stmt), expr(e)
    {}	
};

class WhileIterationStatement : public IterationStatement {
public:
    const Expression* expr;
    WhileIterationStatement(const Expression* e, const Statement* stmt)
	: IterationStatement(stmt), expr(e) 
    {}

};

class ForIterationStatement : public IterationStatement {
public:
    const Expression* refexpr;
    const Expression* testexpr;
    const Expression* incexpr;
    ForIterationStatement(const Expression* init, const Expression* test, const Expression* inc, const Statement* stmt)
	: IterationStatement(stmt), refexpr(init), testexpr(test), incexpr(inc)
    {}
};

class ForVarIterationStatement : public IterationStatement {
public:
    VariableDecList* vars;
    const Expression* testexpr;
    const Expression* incexpr;
    ForVarIterationStatement(VariableDecList* v, const Expression* test, const Expression* inc, const Statement* stmt)
	: IterationStatement(stmt), vars(v), testexpr(test), incexpr(inc) 
    {}
};

class ForInIterationStatement : public IterationStatement {
public:
    const Expression* left;
    const Expression* expr;
    ForInIterationStatement(const Expression* l, const Expression* e, const Statement* stmt)
	: IterationStatement(stmt), left(l), expr(e) 
    {}
};

class ForVarInIterationStatement : public IterationStatement {
public:
    const VariableDec* var;
    const Expression* expr;
    ForVarInIterationStatement(const VariableDec* v, const Expression* e, const Statement* stmt)
	: IterationStatement(stmt), var(v), expr(e) 
    {}
};












