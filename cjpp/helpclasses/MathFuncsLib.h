#include <string>
#include <sstream>
#include "value.h"
//#include "Values.h"
#include <typeinfo>

using namespace std;

class MathFuncs{
public:
    /**
     Addition function with returning Value.	
     */
    template<typename L, typename R>
    static auto addV(L lval, R rval){
        using dispatch_type = integral_constant<
        	bool,
        	is_convertible<L, string>{} || is_convertible<R, string>{} >;
        return do_addV(lval, rval, dispatch_type());
    }
    
    template<typename L, typename R>
    static Value* do_addV(L lval, R rval, false_type){
        Value* val;

        if(std::is_same<decltype(lval),float>::value || std::is_same<decltype(rval),float>::value){
			val = new FloatValue(((float)lval + rval));
        }else{
        	val = new IntegerValue(((int)lval + rval));
        }
        
        return val;
    }
    
    template<typename L, typename R>
    static Value* do_addV(L lval, R rval, true_type){
        ostringstream oss;
        oss << lval << rval;
        StringValue* sval = new StringValue(oss.str());
        return sval;
    }
    
	/* \deprecated { Uses template instead of objects }
	 * Addition function.
	 */
	template<typename L, typename R>
	static auto add(L lval, R rval){
		using dispatch_type = integral_constant<
			bool, 
			is_convertible<L, string>{}
			|| is_convertible<R, string>{} >;
		return do_add(lval, rval, dispatch_type());
	}
    
	/* \deprecated { Uses template instead of objects }
     */
    template<typename L, typename R>
    static auto do_add(L lval, R rval, false_type){
        return lval + rval;
    }
    
    /* \deprecated { Uses template instead of objects }
     */
    template<typename L, typename R>
    static string do_add(L lval, R rval, true_type){
        ostringstream oss;
        oss << lval << rval;
        return oss.str();
    }
        
	/* \deprecated { Uses template instead of objects }
     * Subtraction function.
     */
    template<typename L, typename R>
    static auto sub(L lval, R rval){
        using dispatch_type = integral_constant<
            bool,
            is_convertible<L, string>{}
            || is_convertible<R, string>{} >;
        return do_sub(lval, rval, dispatch_type());
    }
    
    /* \deprecated { Uses template instead of objects }
     */
    template<typename L, typename R>
    static auto do_sub(L lval, R rval, false_type){
        return lval - rval;
    }
    
    /* \deprecated { Uses template instead of objects }
     */
    template<typename L, typename R>
    static string do_sub(L lval, R rval, true_type){
        return "NaN";
    }

	/*
	 *	Comparators usings the object value
	 *
	 *
	 */

	static int do_cmp(Value* lval, Value* rval)
	{
		int ltype = lval->returnType();
		int rtype = rval->returnType();
		switch(ltype) {
			case 1:
				if ((rtype == 1) || (rtype == 3))
					return comparenumbers(lval, rval, ltype, rtype);
				break;
			case 2:
				break;
			case 3:
				if ((rtype == 1) || (rtype == 3))
					return comparenumbers(lval, rval, ltype, rtype);
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			default:
				break;
		}
		return 0;
	}

	static int comparenumbers(Value* lval, Value* rval, int ltype, int rtype)
	{
		float lValue = 0;
		float rValue = 0;

		if (ltype == 1)
		{
			IntegerValue* lvalue = dynamic_cast<IntegerValue*>(lval);
			lValue = lvalue->val;
		}
		if (ltype == 3)
		{
			FloatValue* lvalue = dynamic_cast<FloatValue*>(lval);
			lValue = lvalue->val;
		}
		if (rtype == 1)
		{
			IntegerValue* rvalue = dynamic_cast<IntegerValue*>(rval);
			rValue = rvalue->val;
		}
		if (rtype == 3)
		{
			FloatValue* rvalue = dynamic_cast<FloatValue*>(rval);
			rValue = rvalue->val;
		}
		
		float sign = lValue - rValue;
		if (sign > 0)
			return 1;
		else if (sign < 0)
			return -1;
		else
			return 0;	
	}

	static int comparestring(Value* lval, Value* rval)
	{
		return 0;
	}

	static auto lssthan(Value* lval, Value* rval)
	{
		int result = do_cmp(lval, rval);
		if (result == -1)
		{
			BooleanValue* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			BooleanValue* bval = new BooleanValue(false);
			return bval;
		}
	}

	static auto gtrthan(Value* lval, Value* rval)
	{
		int result = do_cmp(lval, rval);
		if (result == 1)
		{
			BooleanValue* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			BooleanValue* bval = new BooleanValue(false);
			return bval;
		}
	}

	static auto leqthan(Value* lval, Value* rval)
	{
		int result = do_cmp(lval, rval);
		if ( result == -1 || result == 0)
		{
			BooleanValue* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			BooleanValue* bval = new BooleanValue(false);
			return bval;
		}
	}

	static auto geqthan(Value* lval, Value* rval)
	{
		int result = do_cmp(lval, rval);
		if (result == 1 || result == 0)
		{
			BooleanValue* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			BooleanValue* bval = new BooleanValue(false);
			return bval;
		}
	}

	static auto equalto(Value* lval, Value* rval)
	{
		int result = do_cmp(lval, rval);
		if (result == 0)
		{
			BooleanValue* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			BooleanValue* bval = new BooleanValue(false);
			return bval;
		}
	}

	static auto neqto(Value* lval, Value* rval)
	{
		int result = do_cmp(lval, rval);
		if (result != 0)
		{
			BooleanValue* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			BooleanValue* bval = new BooleanValue(false);
			return bval;
		}
	}
};
