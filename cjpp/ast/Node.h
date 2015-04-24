#include <iostream>

class Node {
public:
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
    const Identifier* i;	
    const Literal* l;
    PrimaryExpression(const Identifier* i)
	: i(i)
    {}	
    PrimaryExpression(const Literal* l)
	: l(l)
    {}	
};


