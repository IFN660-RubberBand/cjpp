#ifndef MEMEXPR
#define MEMEPRY


class MemberExpression : public Expression {
public:
    const Expression* expr;
    IdentifierList* l;
    MemberExpression(const Expression* expr) : expr(expr)
    {
		l = new IdentifierList();
	}
    
	~MemberExpression() {
        delete expr;
        delete l;
    }
    void append(Identifier* i) {
    	l->append(i);	
	}
	
    void print(unsigned int tabs) const {
        Expression::print(tabs);
        expr->print(tabs);
        for(list<const Identifier*>::iterator iter = l->ident->begin();
    	    iter != l->ident->end();
            iter++)
		{
			cout << ".";
        	(*iter)->print(0);  
        }
    } 
	
	bool generateCode(TempVariable* result) const {
		bool del = expr->generateCode(result);

			for(list<const Identifier*>::iterator iter = l->ident->begin();
    	    iter != l->ident->end();
            iter++)
		{
        	cout << result->toString() << "->resolve(\"" << (*iter)->toString() << "\");" << endl;  
        }	
		return del;
	}  
	
	void generateLeftHandCode(TempVariable* result) const {
    	expr->generateLeftHandCode(result);
			
		for(list<const Identifier*>::iterator iter = l->ident->begin();
    	    iter != l->ident->end();
            iter++)
		{
        	cout << result->toString() << "->resolve(\"" << (*iter)->toString() << "\");" << endl;  
        }	
	}
	
	bool generateRightHandCode(TempVariable* result) const {
    	expr->generateRightHandCode(result);
			
		for(list<const Identifier*>::iterator iter = l->ident->begin();
    	    iter != l->ident->end();
            iter++)
		{
        	cout << result->toString() << "->resolve(\"" << (*iter)->toString() << "\");" << endl;  
        }	
        return false;
	}
};


#endif
