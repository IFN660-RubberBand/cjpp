/*
 This is a testing class!
 */

#ifndef _Values_h
#define _Values_h

#include <stdint.h>

using namespace std;

enum ValueTypesEnum {
    UndefinedTypeE  = 0,
    BooleanTypeE    = 1,
    IntValueE       = 2,
    FloatValueE     = 3,
    StringValueE    = 4,
    ObjectTypeE     = 5
};

class Value {
public:
    virtual Value* create() = 0;
    
    virtual ValueTypesEnum getType() = 0;
    
    Value* max(Value* other){
        if(getType() > other->getType()){
            return this;
        }else{
            return other;
        }
    }
};

template <ValueTypesEnum MyType, class ValueT>
class ValueFactory: public Value {
public:
    ValueTypesEnum getType(){
        return MyType;
    }
    Value* create(){
        return new ValueT();
    }
};

class IntValue: public ValueFactory<IntValueE, IntValue>{
public:
    int32_t* val;
    
    IntValue(){}
    
    IntValue(int* ival){
        this->set(ival);
    }
    
    void set(int* ival){
        val = static_cast<int32_t*>(ival);
    }
};

class FloatValue: public ValueFactory<FloatValueE, FloatValue>{
};

#endif
