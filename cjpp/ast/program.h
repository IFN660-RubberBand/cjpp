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
		cout << "Generated code in file 'output.c'" << endl;
		std::streambuf *psbuf, *backup;
		std::ofstream myfile;
		myfile.open ("output.c");
		// redirect cout to file
		backup = std::cout.rdbuf();
		psbuf = myfile.rdbuf();
		std::cout.rdbuf(psbuf);
		//
		cout << "int main(int argc, char* argv[]) {" << endl;
		l->generateCode();
		cout << "return 0;" << endl << "}" << endl; 
		std::cout.rdbuf(backup);
		myfile.close();
	}
	
};


#endif
