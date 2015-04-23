#include <iostream>

class SourceElement_node {
public:
	virtual ~Node() {}
};

class Expression_node : public SourceElement_node {
};

class Statement_node: public SourceElement_node {
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