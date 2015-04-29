#include <iostream>
#include <list>
#include <string>
#include <sstream>

#ifndef _NODE
#define _NODE

#define indent(x) { for(unsigned int i = 0; i < x; i++) cout << "\t"; }
using namespace std;

class Node {
public:
    Node() {};
    virtual void print(unsigned int tabs) const = 0;
    virtual ~Node() {};
};

class Statement : public Node {

};

namespace patch 
{
    template < typename T > std::string to_string( const T& n)
    {
        std::ostringstream stm ;
        stm << n;
        return stm.str();
    }
}

class Expression : public Node {
public:
    Expression* pointer;
    Expression() : pointer(NULL) 
    {};
    void prepend(Expression* p) {
        pointer = p;
    }
    void print(unsigned int tabs) const {
        if(pointer != NULL) { 
			pointer->print(tabs);
            cout << " , ";
	}
    }
};

class Literal : public Node {
public:

};

class NumericLiteral : public Literal {
public:
    double value;
    NumericLiteral(const double value) : value(value) {}
    void print(unsigned int tabs) const {
        std::cout << patch::to_string(value);
    }
};



class Identifier : public Node {
public:
    char* name;
    
    Identifier(char* name) : name(name)
    {}	
    void print(unsigned int tabs) const {
        cout << name;
    }
};

class VariableDec : public Node {
public:
    const Identifier* i;
    const Expression* expr;
    VariableDec(Identifier* i) : i(i)
    {
        expr = NULL;
    }
    VariableDec(Identifier* i, Expression* expr) : i(i), expr(expr)
    {}		
    void print(unsigned int tabs) const {
        i->print(tabs);
		if(expr != NULL) {
            cout << " = ";
            expr->print(tabs);
        }
    }
};


class BinaryExpression : public Expression {
public:
    const Expression* left;	
	int op;
    const Expression* right;
    BinaryExpression(const Expression* left, int op, const Expression* right)
	: left(left), op(op), right(right)
    {}
    void print(unsigned int tabs) const {
	Expression::print(tabs);
        left->print(tabs);
	cout << " " << (char) op << " ";
	right->print(tabs);
    }	
};


class TernaryExpression : public Expression {
public:
    const Expression* test;
    const Expression* left;	
    const Expression* right;
    TernaryExpression(const Expression* test, const Expression* left, const Expression* right)
	: test(test), left(left), right(right)
    {}
    void print(unsigned int tabs) const {
	Expression::print(tabs);
        test->print(tabs);
	cout << " ? ";
	left->print(tabs);
	cout << " : ";
	right->print(tabs);
    }	
};



class UnaryExpression : public Expression {
public:
    int op;
    const Expression* expr;
    UnaryExpression(int op, const Expression* expr)
	: op(op), expr(expr)
    {}
    void print(unsigned int tabs) const {
        Expression::print(tabs);
	    expr->print(tabs);
        cout << " " << (char) op << " ";
    }	
};

class PostfixExpression : public Expression {
public:
    const Expression* expr;
	int op;
    PostfixExpression(const Expression* expr, int op)
	: expr(expr), op(op)
    {}
    void print(unsigned int tabs) const {
	Expression::print(tabs);
        cout << " " << (char) op << " ";
	expr->print(tabs);
    }	
};

class AssignmentExpression : public Expression {
public:
    const Expression* left;	
	int op;
    const Expression* expr;
    
    AssignmentExpression(const Expression* left, const Expression* expr)
	: left(left), expr(expr)
    {
        op = NULL;
    }
    AssignmentExpression(const Expression* left, int op, const Expression* expr)
	: left(left), op(op), expr(expr)
    {}
    void print(unsigned int tabs) const {
		Expression::print(tabs);
        left->print(tabs);
		if(op != NULL)
			cout << " " << (char) op << "= ";
		else
			cout << " = ";
		expr->print(tabs);
	}		
};


class PrimaryExpression : public Expression {
public:
    const Node* i;	
    PrimaryExpression(const Node* i)
	: i(i)
    {}	
    void print(unsigned int tabs) const {
        Expression::print(tabs);
	i->print(tabs);
    }	
};

class StatementList : public Node {
public:
    list<const Statement*>* stmts;	
    StatementList(const Statement* s)
    {
         stmts = new list<const Statement*>();
	 append(s);	
    }
    StatementList()
    {
         stmts = new list<const Statement*>();
    }	
    void append(const Statement* s) 
    {
	 stmts->push_back(s);
    }
    void print(unsigned int tabs) const {
        for(list<const Statement*>::iterator iter = stmts->begin();
    	    iter != stmts->end();
            iter++)
		{
        	(*iter)->print(tabs);  
        }	
    }	
};

class ExpressionList : public Expression {
public:
    list<const Expression*>* stmts;	
    ExpressionList(const Expression* s)
    {
         stmts = new list<const Expression*>();
	 append(s);	
    }
    ExpressionList()
    {
         stmts = new list<const Expression*>();
    }	
    void append(const Expression* s) 
    {
	 stmts->push_back(s);
    }
    void print(unsigned int tabs) const {
         for(list<const Expression*>::iterator iter = stmts->begin();
    	    iter != stmts->end();
            iter++)
	 	{
        	(*iter)->print(tabs);  
        }	
    }	
};



class VariableDecList : public Node {
public:
    list<const VariableDec*>* stmts;	
    VariableDecList(const VariableDec* v)
    {
        stmts = new list<const VariableDec*>();
	 	append(v);	
    }
    VariableDecList()
    {
         stmts = new list<const VariableDec*>();
    }	
    void append(const VariableDec* s)
    {
	 stmts->push_back(s);
    }
    void print(unsigned int tabs) const {
    	list<const VariableDec*>::iterator iter = stmts->begin();
    	if(iter != stmts->end())
    		(*iter)->print(tabs);
        for(iter++ = stmts->begin(); iter != stmts->end(); iter++)
		{
        	cout << " , ";
			(*iter)->print(tabs);  
        }	
    }	
};

class VariableStatement : public Statement {
public:
    VariableDecList* l;
    VariableStatement(VariableDecList* l) : l(l)
    {}
    void print(unsigned int tabs) const {
        indent(tabs); 
		cout << "var ";
		l->print(tabs);
		cout << ";" << endl;
    }
};

class Block : public Statement {
public:
    StatementList* l;
    Block(StatementList* l) : l(l)
    {}
    void print(unsigned int tabs) const {
	indent(tabs-1); 
	cout << "{" << endl;
	if(l != NULL) l->print(tabs);
	indent(tabs-1); 
	cout << "}" << endl;
    }
};

class ExpressionStatement : public Statement {
public:
    const Expression* expr;
    ExpressionStatement(const Expression* expr) : expr(expr)
    {}
    void print(unsigned int tabs) const {
        indent(tabs); 
	expr->print(tabs);
	cout << ";" << endl;
    }
	
};

class EmptyStatement : public Statement {
public:
    void print(unsigned int tabs) const {
    	indent(tabs); 
		cout << ";" << endl;
    }
	
};

























#endif
