#include "helpclasses/value.h"
#include "helpclasses/Scope.h"
#include "helpclasses/FunctionLib.h"
#include "helpclasses/MathFuncsLib.h"



static Value* foo(list<Value*>* l) {
	Value* tmp0;
	Value* tmp1 = new NumberValue(1.000000);
	Value* tmp2 = new NumberValue(2.000000);
	tmp0 = MathFuncs::addV2(tmp1, tmp2);
	return tmp0;
}


int main(int argc, char* argv[]) {
Scope* currentscope = new Scope();
currentscope->set("foo", new FunctionValue(&foo));

Value* tmp3 = new FunctionValue(&foo);
Value* tmp4;

Value* tmp5 = new StringValue("bar");

tmp4 = FunctionLib::call(tmp5, NULL);
//currentscope->closeScope();
return 0;
}
