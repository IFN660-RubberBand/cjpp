#include "helpclasses/value.h"
#include "helpclasses/Scope.h"
#include "helpclasses/MathFuncsLib.h"
#include "helpclasses/FunctionLib.h"
#include "helpclasses/javascriptObjects.h"




int main(int argc, char* argv[]) {
	Scope* currentscope = new Scope();

	Value* tmp5;
	tmp5 = new FunctionValue(&log);
	currentscope->set("console", new ObjectValue("log", tmp5));


	Value* tmp0;
	Value* tmp1;
	list<Value*>* l = new list<Value*>();
	Value* tmp2;
	tmp2 = new StringValue("huzzah!");
	l->push_back(tmp2);
	tmp1 = currentscope->resolve("console");
	cout << "console" << endl;
	dynamic_cast<ObjectValue*>(tmp1)->resolve("log");
	cout << "log" << endl;
	Value* tmp3;
	tmp3 = FunctionLib::call(currentscope, tmp1, l);
	delete l;

	currentscope->closeScope();
	delete currentscope;
	return 0;
}
