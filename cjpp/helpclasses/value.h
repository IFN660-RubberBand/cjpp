#include <stdint.h>
#include <map>
#include <stdio.h>
#include <string>
#include <iostream>

#ifndef VALUE
#define VALUE



using namespace std;

/**
 * ...
 */
class Value {
public:
    typedef enum{
        UndefinedType,
        IntegerType,
        ObjectType,
        FloatType,
        StringType,
        BooleanType
    } DataType;
    
    virtual DataType returnType(){
        return UndefinedType;
    };
};

/**
 * ...
 */
class UndefinedValue: public Value{
public:
    DataType returnType(){
        return Value::UndefinedType;
    };
};

/**
 * ...
 */
class IntegerValue: public Value{
public:
	int32_t val;
    
	IntegerValue(int32_t val) : val(val){}
    
    DataType returnType(){
        return Value::IntegerType;
    };
};

/**
 * ...
 */
class ObjectValue: public Value{
public:
	map<char*, Value*>* objMap;
    
	ObjectValue() {
		objMap = new map<char*, Value*>();
	}
    
    DataType returnType(){
        return Value::ObjectType;
    };
    
	Value* resolve(char* ident) {
		auto search = objMap->find(ident);
        
    	if(search != objMap->end()){
        	return search->second;
    	}else{
			Value* value = new UndefinedValue();
        	//? (*objMap)[ident] = value;
        	return value;
    	}
	}

	void set(char* ident, Value* value){
		auto search = objMap->find(ident);
    	if(search != objMap->end()) {
			cout << "delete old object" << endl;	
			//delete search->second;
		}
        (*objMap)[ident] = value;
	}
	
};

/**
 * ...
 */
class FloatValue: public Value{
public:
	float val;
    
	FloatValue(float val) : val(val) {}
    
    DataType returnType(){
        return Value::FloatType;
    };
};

/**
 * ...
 */
class StringValue: public Value{
public:
	char* val;
    
	StringValue(char* val) : val(val){}
    
    DataType returnType(){
        return Value::StringType;
    };
};

/**
 * ...
 */
class BooleanValue: public Value{
public:
	bool val;
    
	BooleanValue(bool val) : val(val){}
    
    DataType returnType(){
        return Value::BooleanType;
    };
};



#endif
