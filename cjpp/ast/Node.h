#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>


#ifndef _NODE
#define _NODE

#include "../helpclasses/TempVariableFactory.h"

#define indent(x) { for(unsigned int i = 0; i < x; i++) cout << "\t"; }
using namespace std;

class Node {
public:
    Node() {};
    virtual void print(unsigned int tabs) const = 0;
    virtual ~Node() {};
	virtual	void generateLeftHandCode(TempVariable* result) const {}
	virtual bool generateRightHandCode(TempVariable* result) const {}
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
    ~Expression() {
    	delete pointer;
	}
    void prepend(Expression* p) {
        pointer = p;
    }
    void print(unsigned int tabs) const {
        if(pointer != NULL) { 
			pointer->print(tabs);
            cout << " , ";
		}
    }
    virtual bool generateCode(TempVariable* result) const {};
};

class Literal : public Node {

};

class NumericLiteral : public Literal {
public:
    double value;
    NumericLiteral(const double value) : value(value) {}
    void print(unsigned int tabs) const {
        std::cout << patch::to_string(value);
    }
    bool generateRightHandCode(TempVariable* result) const {
		cout << result->toString() << " = new IntegerValue(" << patch::to_string(value) << ");" << endl;
    	return true;
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
    void generateLeftHandCode(TempVariable* result) const {
    	cout << "currentscope->set(\"" << name << "\", " << result->toString() << ");" << endl;
	}
	bool generateRightHandCode(TempVariable* result) const {
		cout << result->toString() << " = currentscope->resolve(\"" << name << "\");" << endl;
    	return false;
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
    ~VariableDec() {
    	delete i;
		if(expr != NULL)
			delete expr;
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



class TernaryExpression : public Expression {
public:
    const Expression* test;
    const Expression* left;	
    const Expression* right;
    TernaryExpression(const Expression* test, const Expression* left, const Expression* right)
	: test(test), left(left), right(right)
    {}
    ~TernaryExpression() {
    	delete test;
    	delete left;
    	delete right;
	}
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
    ~UnaryExpression() {
    	delete expr;
	}
    void print(unsigned int tabs) const {
        Expression::print(tabs);
	cout << " " << (char) op << " ";
	expr->print(tabs);

    }	
};

class PostfixExpression : public Expression {
public:
    const Expression* expr;
	int op;
    PostfixExpression(const Expression* expr, int op)
	: expr(expr), op(op)
    {}
    ~PostfixExpression() {
    	delete expr;
	}
    void print(unsigned int tabs) const {
		Expression::print(tabs);
        expr->print(tabs);
		cout << " " << (char) op << " ";
	}	
};




class PrimaryExpression : public Expression {
public:
    const Node* i;	
    PrimaryExpression(const Node* i)
	: i(i)
    {}	
    ~PrimaryExpression() {
    	delete i;
	}
    void print(unsigned int tabs) const {
        Expression::print(tabs);
		i->print(tabs);
    }
	void generateLeftHandCode(TempVariable* result)	const {
		i->generateLeftHandCode(result);
	}
	bool generateRightHandCode(TempVariable* result) const {
		return i->generateRightHandCode(result);	
	}
	bool generateCode(TempVariable* result) const {
		return i->generateRightHandCode(result);
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
    ~ExpressionList() {
    	while(!stmts->empty()) {
			delete stmts->front(); 
			stmts->pop_front();
		}
		delete stmts;
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
     ~VariableDecList() {
    	while(!stmts->empty()) {
			delete stmts->front(); 
			stmts->pop_front();
		}
		delete stmts;
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




#endif
