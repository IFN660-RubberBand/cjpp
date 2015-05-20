#ifndef FUNCTIONEXPRESSION
#define FUNCTIONEXPRESSION


#include "Node.h"
#include "../helpclasses/TempVariable.h"
#include "../helpclasses/TempVariableFactory.h"
#include "identifierlist.h"
#include "statementlist.h"


class FunctionExpression : public Expression {

public:
    const Identifier* ident;	
    const IdentifierList* formalparmlist;
    const StatementList* funcbody; //This has to be replaced with Source element list
    FunctionExpression(const Identifier* ident, const IdentifierList* formalparmlist, const StatementList* funcbody)
	: ident(ident), formalparmlist(formalparmlist), funcbody(funcbody)
    {}
    ~FunctionExpression() {
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
