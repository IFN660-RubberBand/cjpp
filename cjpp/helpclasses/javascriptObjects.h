#include "value.h"
#include "Scope.h"



Value* log(Scope* currentscope, list<Value*>* params)
{
	currentscope = currentscope->openScope();

	Value* tmp0;
	if (params != NULL)
	{
		for(int i = 0; i < 2; i++)
		{
			cout << "test" << " ";
		}	
	}
	cout << endl;
	return tmp0;
}