#include <iostream>

class Node {
public:
	virtual ~Node() {}
};

class Expression_node : public Node {
};

class Statement_node: public Node {
};

class IfStatement_node : public Statement_node {
public:

};

class EmptyStatement_node : public Statement_node {
public: 

};

class UnaryExpression_node : public Expression_node {
public:

};
