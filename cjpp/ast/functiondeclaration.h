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
	{	
		for(list<const Identifier*>::iterator iter = formalparmlist->ident->begin();
    	    				iter != formalparmlist->ident->end();
            				iter++)
		{

       		 	(*iter)->print(0);   
			list<const Identifier*>::iterator temp = iter;
			if(++temp != formalparmlist->ident->end())	
				cout << ",";
	       	}			


	}
	cout << ") "<< endl << "{" << endl;
	funcbody->print(tabs+1);
	cout << "}";
		
    }	
    
    void generateFunctions() const {
			
	cout << "Value* " << ident->toString();
	cout << "(Scope* currentscope, list<Value*>* params)" << endl;
		if (formalparmlist != NULL){
			for(list<const Identifier*>::iterator iter = formalparmlist->ident->begin();
    	    				iter != formalparmlist->ident->end();
            				iter++)
			{
				cout << "currentscope->set(\"";
        		 	(*iter)->print(0);   
				cout << "\", params->getNext());" << endl;
	        	}			

		}
	
	cout << "{" << endl;
	cout << "currentscope = currentscope->openScope();" << endl;
	funcbody->generateCode();

	cout << "}" << endl << endl;

	
    		
	}

	
	bool isStatement() const{
		return false;
	}
	
	bool isFunction() const {
		return true;
	}
	
	void generateCode() const 
	{}

	void generateFunctionAssignment() const {
		cout << "currentscope->set(" << "\"" << ident->toString() << "\", " << "new FunctionValue(" << ident->toString() << "));" << endl;
	}
};


#endif
