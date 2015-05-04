#ifndef PROGRAM
#define PROGRAM

#include "statementlist.h"

class Program {
public:
	StatementList* l;	
	Program(StatementList* l) : l(l) 
	{}
	~Program() {
		delete l;
	}
	void print() const {
		cout << endl << endl << "Print of the AST:" << endl;
		l->print(0);
		cout << endl << endl;
	}
	void generateCode() const {
		cout << "Generated code:" << endl;
		cout << "print int main(int argc, char* argv[]) {" << endl;
		l->generateCode();
		cout << "return 0" << endl << "}" << endl; 
	}
	
};


#endif
