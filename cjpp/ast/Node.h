#include <iostream>
#include <list>
using namespace std;

class Node {
public:
    Node() {};
    virtual void print(unsigned int tabs) const = 0;
    virtual ~Node() {};
};

class Statement : public Node {

};

class Expression : public Node {

};

class Literal : public Node {
public:

};

class NumericLiteral : public Literal {
public:
    double value;
    NumericLiteral(const double value) : value(value) {}
    void print(unsigned int tabs) const {
        cout << to_string(value);
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



class ExpressionStatement : public Statement {
public:
    const Expression* expr;
    ExpressionStatement(const Expression* expr) : expr(expr)
    {}
    void print(unsigned int tabs) const {
        for(unsigned int i = 0; i < tabs; i++) {
             cout << "\t";
	}
        expr->print(tabs);
	cout << ";" << endl;
    }
	
};

class LeftHandsideExpression : public Expression {
public:
    	
};

class BinaryExpression : public Expression {
public:
    int op;
    const Expression* left;	
    const Expression* right;
    BinaryExpression(const Expression* left, int op, const Expression* right)
	: left(left), right(right), op(op)
    {}
    void print(unsigned int tabs) const {
        left->print(tabs);
	cout << " " << (char) op << " ";
	right->print(tabs);
    }	
};

class AssignmentExpression : public Expression {
public:
    const Expression* left;	
    const Expression* expr;
    int op;
    AssignmentExpression(const Expression* left, const Expression* expr)
	: left(left), expr(expr)
    {
        op = NULL;
    }
    AssignmentExpression(const Expression* left, int op, const Expression* expr)
	: left(left), expr(expr), op(op)
    {}
    void print(unsigned int tabs) const {
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

