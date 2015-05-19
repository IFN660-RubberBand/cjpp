#ifndef VALUE
#define VALUE

#include <stdint.h>
#include <map>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <string.h>

using namespace std;

/**
 * ...
 */
class Value {
protected:
    typedef enum{
        UndefinedType   = 0,
        IntegerType     = 1,
        ObjectType      = 2,
        FloatType       = 3,
        StringType      = 4,
        BooleanType     = 5,
        NullType        = 6
    } DataType;
    
public:
    int val;
    
    virtual DataType returnType(){
        return UndefinedType;
    }
    virtual bool toBoolean() = 0;
    virtual Value* copy() = 0;
};

/**
 * //todo: Define what a undefined value is.
 */
class UndefinedValue: public Value{
public:
    DataType returnType(){
        return Value::UndefinedType;
    };
    bool toBoolean() {
		return false;
	}
	Value* copy() {
		return new UndefinedValue();
	}
};

class NullValue: public Value{
public:
    DataType returnType(){
        return Value::NullType;
    };
    bool toBoolean() {
		return false;
	}
	Value* copy() {
		return new NullValue();
	}
};

/**
 * Class representing the integer value.
 */
class IntegerValue: public Value{
public:
    /**
     * All JavaScript integer values are based on 32bits.
     */
	int32_t val;
    
	IntegerValue(int32_t val) : val(val){}
    
    /**
     * Return the data type of IntegerValue class.
     * @return Return the integer representing the IntegerType in the enumeration.
     */
    DataType returnType(){
        return Value::IntegerType;
    }
    bool toBoolean() {
		if(val == 0)
			return false;
		return true;	
	}
	Value* copy() {
		return new IntegerValue(val);
	}
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
    
    ObjectValue(char* ident, Value* value): ObjectValue() {
        set(ident, value);
    }
    
    /**
     * @return Return the integer representing the ObjectValue in the enumeration.
     */
    DataType returnType(){
        return Value::ObjectType;
    };
    
    /**
     * @return Return the found object within the resolved scope or else return integer representing the undefined value in the enumeration.
     */
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

    /**
     * ...
     */
	void set(char* ident, Value* value){
		auto search = objMap->find(ident);
    	if(search != objMap->end()) {
			cout << "delete old object" << endl;	
			//delete search->second;
		}
        (*objMap)[ident] = value;
	}
	bool toBoolean() {
		return true;
	}
};

/**
 * ...
 */
class FloatValue: public Value{
public:
	float val;
    
	FloatValue(float val) : val(val) {}
    
    /**
     * @return Return the integer representing the FloatValue in the enumeration.
     */
    DataType returnType(){
        return Value::FloatType;
    };
    bool toBoolean() {
    	if(val == 0 || val == NAN)
    		return false;
    	return true;	
	}
	Value* copy() {
		return new FloatValue(val);
	}
};

/**
 * ...
 */
class StringValue: public Value{
public:
	string val;
    
	StringValue(string val) : val(val){}
    
    /**
     * @return Return the integer representing the StringValue in the enumeration.
     */
    DataType returnType(){
        return Value::StringType;
    };
    
    bool toBoolean() {
    	if(val[0] == '\0')
    		return false;
    	return true;	
	}
	Value* copy() {
		return new StringValue(val);
	}
};

/**
 * ...
 */
class BooleanValue: public Value{
public:
	bool val;
    
	BooleanValue(bool val) : val(val){}
    
    /**
     * @return Return the integer representing the BooleanValue in the enumeration.
     */
    DataType returnType(){
        return Value::BooleanType;
    };
    
    bool toBoolean() {
    	return val;
	}
	Value* copy() {
		return new BooleanValue(val);
	}
};



#endif
