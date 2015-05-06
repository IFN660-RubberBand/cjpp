#include "value.h"
#include <stdio.h>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
	
	char* var1 = "foo";
	char* var2 = "foo";
	char* var3 = "bar";
	Value* content = new IntegerValue(42);
	
	ObjectValue* obj = new ObjectValue();
	obj->set(var1, content);
	
	
	cout << "is it working?" << endl;
	cout << &(*content) << endl; //the address of the original object
		
	Value* tmp1 = obj->resolve(var2); //resolves to the same object
	cout << &(*tmp1) << endl;		  //notice that set is called with var1 but resolve with var2 !!!
	
	Value* tmp2 = obj->resolve(var3);	//doesnt resolve, returns pointer to UndefinedObject
	cout << &(*tmp2) << endl;	 
	
	obj->set(var2, tmp2);			//overwrite the value of foo 
	tmp2 = obj->resolve(var1);		//deletes the old value
	cout << &(*tmp2) << endl;		//now also points to the undefined object
	
	obj->set(var3, new IntegerValue(11));
	tmp2 = obj->resolve(var3);			//now it does resolve
	cout << &(*tmp2) << endl;			//new pointer value
	
	tmp2 = obj->resolve(var2);		//foo still points to the undefined object
	cout << &(*tmp2) << endl;		
	
	return 0;
} 
