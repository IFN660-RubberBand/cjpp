#ifndef FUNCTIONDECLARATION
#define FUNCTIONDECLARATION


#include "Node.h"
#include "../helpclasses/TempVariable.h"
#include "../helpclasses/TempVariableFactory.h"
#include "identifierlist.h"
#include "statement.h"
#include "sourceelementlist.h"


class FunctionDeclaration : public SourceElement {

public:
    const Identifier* ident;	
    const IdentifierList* formalparmlist;
    const SourceElementList* funcbody;
  
    FunctionDeclaration(const Identifier* ident, const IdentifierList* formalparmlist, const SourceElementList* funcbody)
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
    
    void generateFunctions() const {
			
	cout << "Value* " << ident->toString();

		if (formalparmlist != NULL){
			cout << "(List <Value*> params)" << endl;
			cout << "currentscope=currentscope->newScope();" << endl;
			cout << "currentscope->set(\"";
			formalparmlist->generateCode();
			cout << "\", params->getNext());" << endl;
		} else {
			cout << "()" << endl;
		}
	
	cout << "{" << endl;
	funcbody->generateCode();
	cout << "}" << endl;

	cout << "currentScope->set(" << "\"" << ident->toString() <<"\"" << ", " << "new FunctionValue(" << ident->toString() <<"));" << endl ; 
	
    		
	}

	
	bool isStatement() const{
		return false;
	}
	
	bool isFunction() const {
		return true;
	}
	
	void generateCode() const 
	{}
};


#endif
