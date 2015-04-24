#include <iostream>

class Node {
public:
    Node() {};
    virtual ~Node() {};
};

class Statement : public Node {

};

class Literal : public Node {

};

class Expression : public Node {

};


class Identifier : public Node {
public:
    char* name;
    
    Identifier(char* name) : name(name)
    {}	
};



class ExpressionStatement : public Statement {
public:
    const Expression* expr;
    ExpressionStatement(const Expression* expr) : expr(expr)
    {}	
};

class LeftHandsideExpression : public Expression {
public:
    	
};

class AssignmentExpression : public Expression {
public:
    const Expression* left;	
    const Expression* expr;
    AssignmentExpression(const Expression* left, const Expression* expr)
	: left(left), expr(expr)
    {}		
};


class PrimaryExpression : public Expression {
public:
    const Node* i;	
    PrimaryExpression(const Node* i)
	: i(i)
    {}	
};


