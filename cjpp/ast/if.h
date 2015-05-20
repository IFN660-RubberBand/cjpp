#ifndef _IF
#define _IF

#include "Node.h"

class IfStatement : public Statement {
public:
	const Statement* ifstmt;
	const Statement* elsestmt;
	const Expression* expr;
	IfStatement(const Expression* expr, Statement* ifs, Statement* elses)
	: expr(expr), ifstmt(ifs), elsestmt(elses) 
	{}
	~IfStatement() {
		delete expr;
		delete ifstmt;
		if(elsestmt != NULL)
			delete elsestmt;
	}
	void print(unsigned int tabs) const{
		indent(tabs);
		cout << "if (";
		expr->print(tabs);
		cout << ")" << endl;
		ifstmt->print(tabs+1);
		if (elsestmt != NULL) {
			indent(tabs);
			cout << "else" << endl;
			elsestmt->print(tabs+1);
		}
	}
	
	void generateCode() const {
		TempVariable* t = TempVariableFactory::getTemp();
        JumpLabel* jumpElse= JumpLabelFactory::getLabel();
        JumpLabel* jumpEnd= JumpLabelFactory::getLabel();

		expr->generateCode(t);

		cout << "if (!" << t->toString() << "->toBoolean()" << ") " << "goto " << jumpElse->toString() <<";"<< endl;
        ifstmt->generateCode();
		cout << "goto " << jumpEnd->toString() << ";" << endl;

        /*
         *First need to check if else condition exists.  If not, jump straight to End:
         */
        cout<<jumpElse->toString()<<":"<<endl; //Else Label
        	if (elsestmt != NULL) {
				elsestmt->generateCode();
			} else {
				cout << "goto " << jumpEnd->toString() <<";" << endl;
			}


		/*
		 *End label
		 */
        cout<<jumpEnd->toString()<<":"<<endl; 
        delete t;
        delete jumpElse;
		delete jumpEnd;
		
	}


};

#endif
