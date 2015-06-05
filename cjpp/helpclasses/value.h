#ifndef VALUE
#define VALUE

#include <stdint.h>
#include <map>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <string.h>
#include <boost/lexical_cast.hpp>
#include <list>


using namespace std;

/**
 * ...
 */
class Value {
protected:
    typedef enum {
        NullType        = 0,
        IntegerType     = 1,
        FloatType       = 2,
        BooleanType     = 3,
        UndefinedType   = 4,
        ObjectType      = 5,
        StringType      = 6,
        FunctionType	= 7,
        NaNType         = 8
    } DataType;
    
public:
    virtual bool toBoolean() = 0;
    virtual float toFloat() = 0;
    virtual string toString() = 0;
    virtual Value* copy() = 0;
    virtual DataType returnType() = 0;
    virtual ~Value() {  }
};

/**
 * //todo: Define what a undefined value is.
 */
class UndefinedValue: public Value {
public:
    bool toBoolean() {
        return false;
    }
    float toFloat() {
        return 0;
    }
    string toString() {
        return "Undefined";
    }
	Value* copy() {
		return new UndefinedValue();
	}
    DataType returnType() {
        return Value::UndefinedType;
    }
};

/**
 * ...
 */
class NaNValue: public Value{
public:
    bool toBoolean() {
        return false;
    }
    float toFloat() {
        return 0;
    }
    string toString() {
        return "NaN";
    }
    Value* copy() {
        return new NaNValue();
    }
    DataType returnType() {
        return Value::NaNType;
    }
};

/**
 * ...
 */
class NullValue: public Value{
public:
    bool toBoolean() {
		return false;
	}
    float toFloat() {
        return 0;
    }
    string toString() {
        return "null";
    }
	Value* copy() {
		return new NullValue();
	}
    DataType returnType() {
        return Value::NullType;
    }
};

/**
 * ...
 */
class NumberValue: public Value {
public:
    float val;
    
    NumberValue(float val) : val(val) {}

    bool toBoolean() {
        if(val) {
            return true;
        }
        return false;
    }
    float toFloat() {
        return val;
    }
    string toString() {
        return to_string(val);
    }
    Value* copy() {
        return new NumberValue(val);
    }
    /**
     * @return Return the integer representing the FloatValue in the enumeration.
     */
    DataType returnType() {
        return Value::FloatType;
    }
};

/**
 * Class representing the integer value.
 */
class IntegerValue: public Value {
public:
    /**
     * All JavaScript integer values are based on 32bits.
     */
	int32_t val;
    
	IntegerValue(int32_t val) : val(val){}

    bool toBoolean() {
		if(val)
			return true;
		return false;
	}
    float toFloat() {
        return val;
    }
    string toString() {
        return to_string(val);
    }
	Value* copy() {
		return new IntegerValue(val);
	}
    /**
     * Return the data type of IntegerValue class.
     * @return Return the integer representing the IntegerType in the enumeration.
     */
    DataType returnType(){
        return Value::IntegerType;
    }
};

/**
 * ...
 */
class ObjectValue: public Value {
public:
	map<char*, Value*>* objMap;
    
	ObjectValue() {
		objMap = new map<char*, Value*>();
	}
    
    ObjectValue(char* ident, Value* value): ObjectValue() {
        set(ident, value);
    }
    
    /**
     * @return Return the found object within the resolved scope or else return integer representing the undefined value in the enumeration.
     */
	Value* resolve(char* ident) {
		auto search = objMap->find(ident);
        
    	if(search != objMap->end()){
        	return search->second;
    	}else{
			Value* value = new UndefinedValue();
        	return value;
    	}
	}

    /**
     * ...
     */
	void set(char* ident, Value* value) {
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
    float toFloat() {
        return 0;
    }
    Value* copy() {
        return new ObjectValue();
    }

    string toString() {
        return "Object";
    }
    /**
     * @return Return the integer representing the ObjectValue in the enumeration.
     */
    DataType returnType() {
        return Value::ObjectType;
    }
};

/**
 * ...
 */
class FloatValue: public Value {
public:
	float val;
    
	FloatValue(float val) : val(val) {}
    
    bool toBoolean() {
    	if(val)
    		return true;
    	return false;
	}
    float toFloat() {
        return val;
    }
    string toString(){
        return to_string(val);
    }
	Value* copy() {
		return new FloatValue(val);
	}
    /**
     * @return Return the integer representing the FloatValue in the enumeration.
     */
    DataType returnType(){
        return Value::FloatType;
    }
};

/**
 * ...
 */
class StringValue: public Value {
public:
	string val;
    
	StringValue(string val) : val(val){}

    bool toBoolean() {
        return val[0] != 0;
        	
	}
    float toFloat() {
        try{
            return boost::lexical_cast<float>(val);
        }catch(const boost::bad_lexical_cast &){
            return NAN;
        }
    }
    string toString() {
        return val;
    }
	Value* copy() {
		return new StringValue(val);
	}
    /**
     * @return Return the integer representing the StringValue in the enumeration.
     */
    DataType returnType() {
        return Value::StringType;
    }
};

/**
 * ...
 */
class BooleanValue: public Value {
public:
	bool val;
    
	BooleanValue(bool val) : val(val){}
    
    bool toBoolean() {
    	return val;
	}
    float toFloat() {
        return NAN;
    }
    string toString() {
        return to_string(val);
    }
	Value* copy() {
		return new BooleanValue(val);
	}
    /**
     * @return Return the integer representing the BooleanValue in the enumeration.
     */
    DataType returnType(){
        return Value::BooleanType;
    }
};





#endif
