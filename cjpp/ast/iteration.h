#ifndef _ITERATION
#define _ITERATION 


#include "Node.h"
#include "../helpclasses/TempVariable.h"
#include "../helpclasses/TempVariableFactory.h"
#include "../helpclasses/JumpLabelFactory.h"
#include "../helpclasses/JumpLabel.h"


class IterationStatement : public Statement {
public:
    const Statement* stmt;
    IterationStatement(const Statement* s) : stmt(s) 
    {}
    ~IterationStatement() {
    	delete stmt;
	}
    void generateCode() const {
    	cout << "not yet implementd iteration" << endl;
	}
};

class DoWhileIterationStatement : public IterationStatement {
public:
    const Expression* expr;
    DoWhileIterationStatement(const Statement* stmt, const Expression* e)
	: IterationStatement(stmt), expr(e)
    {}	
    ~DoWhileIterationStatement() {
    	delete expr;
	}
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
    ~WhileIterationStatement() {
    	delete expr;
	}
    void print(unsigned int tabs) const {
	indent(tabs); 
	cout << " while ( ";
	expr->print(tabs);
	cout << " ) " << endl;
	stmt->print(tabs+1);
    }
    
    void generateCode() const {
    	TempVariable* t = TempVariableFactory::getTemp();
    	JumpLabel* check = JumpLabelFactory::getLabel();	
		JumpLabel* end = JumpLabelFactory::getLabel();		
		
		cout << "//While-loop" << endl;
		//generate check jump label	
    	cout << check->toString() << ":" << endl;
    	
		//generate code for expression
    	bool free = expr->generateCode(t);
    	
		cout << "if(!" << t->toString() << "->toBoolean()) " << "goto " << end->toString() << ";" << endl;
		stmt->generateCode();
		
		//jump to start
		cout << "goto " << check->toString() << ";" << endl; 
		
		//generate end jump label	
    	cout << end->toString() << ":" << endl;
    	if(free)
    		cout << "delete " << t->toString() << ";" << endl;
		
		cout << "//end of While-loop" << endl;
		delete t;
		delete check;
		delete end;
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
    ~ForIterationStatement() {
    	if(refexpr != NULL)
    		delete refexpr;
    	if(testexpr != NULL)
    		delete testexpr;
    	if(incexpr != NULL)
    		delete incexpr;
	}
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
    
    void generateCode() const {
    	TempVariable* ref = TempVariableFactory::getTemp();
    	TempVariable* test = TempVariableFactory::getTemp();
    	TempVariable* inc = TempVariableFactory::getTemp();
    	JumpLabel* end = JumpLabelFactory::getLabel();	
		JumpLabel* check = JumpLabelFactory::getLabel();	
		
		cout << "//For-loop" << endl;
		
		//generate code for ref expression
		if(refexpr != NULL) {
			bool free_ref = refexpr->generateCode(ref);
			if(free_ref)
				cout << "delete " << ref->toString() << ";" << endl;
		}	
    	
    	//label for check
		cout << check->toString() << ":" << endl;
		
		//generate code for test expression
		bool free_test = false;
		if(testexpr != NULL) {
			free_test = testexpr->generateCode(test);
		}
		
		cout << "if(!" << test->toString() << "->toBoolean()) " << "goto " << end->toString() << ";" << endl;
		
		stmt->generateCode();
		
		//generate code for inc expression
    	if(incexpr != NULL) {
			bool free_inc = incexpr->generateCode(inc);
			if(free_inc)
				cout << "delete " << inc->toString() << ";" << endl;
		}
    	
		//jump to check
		cout << "goto " << check->toString() << ";" << endl; 
		
		//generate end jump label	
    	cout << end->toString() << ":" << endl;
		if(free_test)
			cout << "delete " << test->toString() << ";" << endl;
		
		cout << "//end of For-loop" << endl;
		
		delete test;
		delete ref;
		delete inc;
		delete check;
		delete end;
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
    ~ForVarIterationStatement() {
    	delete vars;
    	if(testexpr != NULL)
    		delete testexpr;
    	if(incexpr != NULL)
    		delete incexpr;
	}
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
    
     void generateCode() const {
    	TempVariable* ref = TempVariableFactory::getTemp();
    	TempVariable* test = TempVariableFactory::getTemp();
    	TempVariable* inc = TempVariableFactory::getTemp();
    	JumpLabel* end = JumpLabelFactory::getLabel();	
		JumpLabel* check = JumpLabelFactory::getLabel();	
		
		cout << "//ForVar-loop" << endl;
		
		//generate code for ref expression
		if(vars != NULL) {
			bool free_ref = vars->generateCode(ref);
			if(free_ref)
				cout << "delete " << ref->toString() << ";" << endl;
		}	
    	
    	//label for check
		cout << check->toString() << ":" << endl;
		
		//generate code for test expression
		bool free_test = false;
		if(testexpr != NULL) {
			free_test = testexpr->generateCode(test);
		}
		
		cout << "if(!" << test->toString() << "->toBoolean()) " << "goto " << end->toString() << ";" << endl;
		
		stmt->generateCode();
		
		//generate code for inc expression
    	if(incexpr != NULL) {
			bool free_inc = incexpr->generateCode(inc);
			if(free_inc)
				cout << "delete " << inc->toString() << ";" << endl;
		}
    	
		//jump to check
		cout << "goto " << check->toString() << ";" << endl; 
		
		//generate end jump label	
    	cout << end->toString() << ":" << endl;
		if(free_test)
			cout << "delete " << test->toString() << ";" << endl;
		
		cout << "//end of ForVar-loop" << endl;
		
		delete test;
		delete ref;
		delete inc;
		delete check;
		delete end;
	}
};

class ForInIterationStatement : public IterationStatement {
public:
    const Expression* left;
    const Expression* expr;
    ForInIterationStatement(const Expression* l, const Expression* e, const Statement* stmt)
	: IterationStatement(stmt), left(l), expr(e) 
    {}
    ~ForInIterationStatement() {
    	delete left;
    	delete expr;
	}
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
    ~ForVarInIterationStatement() {
    	delete var;
    	delete expr;
	}
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








