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
    const SourceElementList* funcbody;
    FunctionExpression(const Identifier* ident, const IdentifierList* formalparmlist, const SourceElementList* funcbody)
	: ident(ident), formalparmlist(formalparmlist), funcbody(funcbody)
    {}
    ~FunctionExpression() {
    	delete ident;
        delete formalparmlist;
    	delete funcbody;
	}
    void print(unsigned int tabs) const {
		cout << "not implemented yet" << endl;
    }	
    
    bool generateCode(TempVariable* result) const {
        cout << "not implemented yet" << endl;
        return 0;		
	}
	
	
	
};


#endif
