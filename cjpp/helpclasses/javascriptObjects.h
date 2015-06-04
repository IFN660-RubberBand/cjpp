#include "value.h"
#include "Scope.h"

using namespace std;


Value* log(Scope* currentscope, list<Value*>* params)
{
	currentscope = currentscope->openScope();

	Value* tmp0;
	if (params != NULL)
	{
		for(list<Value*>::iterator iter = params->begin();
				iter != params->end();
				iter++)
		{
			cout << (*iter)->toString() << " ";
		}	
	}
	cout << endl;
	return tmp0;
}