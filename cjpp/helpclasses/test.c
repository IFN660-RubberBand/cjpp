#include "value.h"
#include <stdio.h>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
	
	char* var = "i";
	Value* cont = new IntegerValue(42);
	
	cout << "point 1" << endl;
	ObjectValue obj;
	cout << "point 2" << endl;
	
	
	obj.set(var, cont);
	Value* tmp = obj.resolve(var);
	
	cout << &(*cont) << endl;
	cout << &(*tmp);
	
	
	return 0;
} 
