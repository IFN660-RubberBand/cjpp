#include "ast.h"

class IterationStatement : public Statement_node {
public:
    Statement_node* stmt;
    IterationStatement(const Statement_node* s) 
    {
         stmt = s;
    }

};

class DoWhileIterationStatement : public IterationStatement {
public:
    Expression_node* expr;
    DoWhileIterationStatement(const Statement_node* stmt, const Expression_node* e)
	: IterationStatement(stmt) 
    {
       expr = e;
    }	
};

class WhileIterationStatement : public IterationStatement {
public:
    Expression_node* expr;
    WhileIterationStatement(const Expression_node* e, const Statement_node* stmt)
	: IterationStatement(stmt) 
    {
       expr = e;
    }
};

class ForIterationStatement : public IterationStatement {
public:
    Expression_node* refexpr;
    Expression_node* testexpr;
    Expression_node* incexpr;
    ForIterationStatement(const Expression_node* init, const Expression_node* test, const Expression_node* inc, const Statement_node* stmt)
	: IterationStatement(stmt) 
    {
       refexpr = init;
       testexpr = test;
       incexpr = inc;
    }
};

class ForVarIterationStatement : public IterationStatement {
public:
    variableDeclList* vars;
    Expression_node* testexpr;
    Expression_node* incexpr;
    ForVarIterationStatement(const variableDeclList* v, const Expression_node* test, const Expression_node* inc, const Statement_node* stmt)
	: IterationStatement(stmt) 
    {
       vars = v;
       testexpr = test;
       incexpr = inc;
    }
};

class ForInIterationStatement : public IterationStatement {
public:
    LeftHandSideExpresion* left;
    Expression_node* expr;
    ForInIterationStatement(const LeftHandSideExpresion* l, const Expression_node* e, const Statement_node* stmt)
	: IterationStatement(stmt) 
    {
       left = l;
       expr = e;
    }
};

class ForVarIterationStatement : public IterationStatement {
public:
    variableDeclList* vars;
    Expression_node* expr;
    ForVarIterationStatement(const variableDeclList* v, const Expression_node* e, const Statement_node* stmt)
	: IterationStatement(stmt) 
    {
       vars = v;
       expr = e;
    }
};