#ifndef PROGRAM
#define PROGRAM

#include "sourceelementlist.h"

class Program {
public:
	SourceElementList* l;	
	Program(SourceElementList* l) : l(l) 
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
		
		cout << "#include \"helpclasses/value.h\"" << endl;
		cout << "#include \"helpclasses/Scope.h\"" << endl;
		cout << "#include \"helpclasses/MathFuncsLib.h\"" << endl;
		cout << "#include \"helpclasses/FunctionLib.h\"" << endl;
		cout << "#include \"helpclasses/javascriptObjects.h\"" << endl << endl;
		
		l->generateFunctions();
		
		
		cout << endl << "int main(int argc, char* argv[]) {" << endl;
		cout << "Scope* currentscope = new Scope();" << endl; 
		cout << "list<Value*>* l;" << endl;
		cout << "setGlobalObjects(currentscope);"<< endl << endl;
		
		l->generateFunctionAssignment();
		
		TempVariableFactory::reset();
		l->generateCode();
		cout << endl << "currentscope->closeScope();" << endl;
		cout << "delete currentscope;" << endl;
		cout <<"return 0;" << endl << "}" << endl; 
		std::cout.rdbuf(backup);
		myfile.close();
	}
	
};


#endif
