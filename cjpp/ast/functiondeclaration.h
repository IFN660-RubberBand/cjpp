#ifndef FUNCTIONDECLARATION1
#define FUNCTIONDECLARATION1


#include "Node.h"
#include "../helpclasses/TempVariable.h"
#include "../helpclasses/TempVariableFactory.h"
#include "identifierlist.h"
#include "statementlist.h"
#include "statement.h"

class FunctionDeclaration : public Expression {

public:
    const Identifier* ident;	
    const IdentifierList* formalparmlist;
    const StatementList* funcbody;
  
    FunctionDeclaration(const Identifier* ident, const IdentifierList* formalparmlist, const StatementList* funcbody)
	: ident(ident), formalparmlist(formalparmlist), funcbody(funcbody)
    {}
    ~FunctionDeclaration() {
    	delete ident;
    	delete formalparmlist;
	delete funcbody;
	}
    
void print(unsigned int tabs) const {
	indent(tabs);
	cout << "function ";


	ident->print(tabs);
	cout<<" (";

	if(formalparmlist != NULL)	
		formalparmlist->print(tabs);

	cout << ") "<< endl << "{" << endl;
	funcbody->print(tabs+1);
	cout << "}";
		
    }	
    
    bool generateCode(TempVariable* result) const {
			
	cout << "Value* " << ident->toString() << "(Value* ";
	formalparmlist->generateCode();
	cout << ")" << endl;
	cout << "{" << endl;
	funcbody->generateCode();
	cout << "}" << endl;

	cout << "currentScope->set(" << "\"" << ident->toString() <<"\"" << ", " << "new FunctionValue(" << ident->toString() <<"));" << endl ; 
	
    		
	}

	
	
	
};


#endif
