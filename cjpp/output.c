#include "helpclasses/value.h"
#include "helpclasses/Scope.h"
#include "helpclasses/MathFuncsLib.h"
#include "helpclasses/FunctionLib.h"
#include "helpclasses/javascriptObjects.h"


int main(int argc, char* argv[]) {
Scope* currentscope = new Scope();
list<Value*>* l;
setGlobalObjects(currentscope);

Value* tmp0;

//Assignment
tmp0 = new NumberValue(1.000000);
tmp0 = currentscope->set("x", tmp0);
Value* tmp1;
Value* tmp2;
tmp1 = currentscope->resolve("x");
tmp2 = new NumberValue(2.000000);
tmp0 = MathFuncs::lssthan(tmp1, tmp2);
delete tmp2;
if (!tmp0->toBoolean()) goto JmpLabel0;

//Assignment
tmp0 = new StringValue("less than two");
tmp0 = currentscope->set("x", tmp0);
goto JmpLabel1;
JmpLabel0:

//Assignment
tmp0 = new StringValue("more than two");
tmp0 = currentscope->set("x", tmp0);
JmpLabel1:
tmp2 = currentscope->resolve("x");
l = new list<Value*>();
l->push_back(tmp2->copy());
tmp1 = currentscope->resolve("console");
tmp1 = dynamic_cast<ObjectValue*>(tmp1)->resolve("log");
tmp0 = FunctionLib::call(currentscope, tmp1, l);
delete l;

currentscope->closeScope();
delete currentscope;
return 0;
}
