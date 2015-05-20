#ifndef FUNCTIONDECLARATION1
#define FUNCTIONDECLARATION1


#include "Node.h"
#include "../helpclasses/TempVariable.h"
#include "../helpclasses/TempVariableFactory.h"
#include "identifierlist.h"
#include "statementlist.h"


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
		
    }	
    
    bool generateCode(TempVariable* result) const {

    		
	}
	
	
	
};


#endif
