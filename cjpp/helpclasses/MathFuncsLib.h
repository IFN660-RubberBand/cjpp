#include <stdio.h>
#include <string>
#include <sstream>
#include "value.h"
//#include "Values.h"
#include <typeinfo>
#include <cmath>

using namespace std;

class MathFuncs{
public:
	/*
	 Current addition function.
	 */
	static Value* addV2(Value* lval, Value* rval){
		Value* sumval = new NullValue();

		if(lval->returnType() <= 3 && rval->returnType() <= 3){
			sumval =  new NumberValue(lval->toFloat() + rval->toFloat());
		}else if(lval->returnType() <= 6 || rval->returnType() <= 6){
			sumval =  new StringValue(lval->toString() + rval->toString());
		}
		
		return sumval;
	}

	/*
	 Current subtraction function.
	 */
	static Value* subV(Value* lval, Value* rval){
		return new NumberValue(lval->toFloat() - rval->toFloat());
	}

	/*
	 Current multiplication function.
	 */
	static Value* multV(Value* lval, Value* rval){
		return new NumberValue(lval->toFloat() * rval->toFloat());
	}

	/*
	 Current division function.
	 */
	static Value* divV(Value* lval, Value* rval){
		return new NumberValue(lval->toFloat() / rval->toFloat());
	}

    /* \deprecated { Uses template instead of objects }
     Addition function with returning Value.	
     */
    // template<typename L, typename R>
    // static auto addV(L lval, R rval){
    //     using dispatch_type = integral_constant<
    //     	bool,
    //     	is_convertible<L, string>{} || is_convertible<R, string>{} >;
    //     return do_addV(lval, rval, dispatch_type());
    // }
    
    /* \deprecated { Uses template instead of objects }
     */
    template<typename L, typename R>
    static Value* do_addV(L lval, R rval, false_type){
        Value* val;

        if(is_same<decltype(lval),float>::value || is_same<decltype(rval),float>::value){
			val = new FloatValue(((float)lval + rval));
        }else{
        	val = new IntegerValue(((int)lval + rval));
        }
        
        return val;
    }
    
    /* \deprecated { Uses template instead of objects }
     */
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
	// template<typename L, typename R>
	// static auto add(L lval, R rval){
	// 	using dispatch_type = integral_constant<
	// 		bool, 
	// 		is_convertible<L, string>{}
	// 		|| is_convertible<R, string>{} >;
	// 	return do_add(lval, rval, dispatch_type());
	// }
    
	/* \deprecated { Uses template instead of objects }
     */
    // template<typename L, typename R>
    // static auto do_add(L lval, R rval, false_type){
    //     return lval + rval;
    // }
    
    /* \deprecated { Uses template instead of objects }
     */
    // template<typename L, typename R>
    // static string do_add(L lval, R rval, true_type){
    //     ostringstream oss;
    //     oss << lval << rval;
    //     return oss.str();
    // }
        
	/* \deprecated { Uses template instead of objects }
     * Subtraction function.
     */
    // template<typename L, typename R>
    // static auto sub(L lval, R rval){
    //     using dispatch_type = integral_constant<
    //         bool,
    //         is_convertible<L, string>{}
    //         || is_convertible<R, string>{} >;
    //     return do_sub(lval, rval, dispatch_type());
    // }
    
    /* \deprecated { Uses template instead of objects }
     */
    // template<typename L, typename R>
    // static auto do_sub(L lval, R rval, false_type){
    //     return lval - rval;
    // }
    
    /* \deprecated { Uses template instead of objects }
     */
    // template<typename L, typename R>
    // static string do_sub(L lval, R rval, true_type){
    //     return "NaN";
    // }

	/*
	 *	Comparators usings the object value
	 *
	 *
	 */

	static int do_cmp(Value* lval, Value* rval)
	{
		int ltype = lval->returnType();
		int rtype = rval->returnType();
		if ((ltype <= 2) && (rtype <= 2))
		{
			return comparenumbers(lval, rval);
		}
		else if ((ltype <= 2 || ltype == 6) && (rtype <=2 || rtype ==6))
		{
			return comparestring(lval, rval, ltype, rtype);
		}
		return 0;
	}

	static int comparenumbers(Value* lval, Value* rval)
	{
		float sign = lval->toFloat() - rval->toFloat();
		if (sign > 0)
			return 1;
		else if (sign < 0)
			return -1;
		else
			return 0;	
	}

	static int comparestring(Value* lval, Value* rval, int ltype, int rtype)
	{
		if ((ltype == 6 && lval->toFloat() != NAN) || (rtype == 6 && rval->toFloat() != NAN))
		{
			return comparenumbers(lval, rval);
		}

		return 0;
	}

	static Value* lssthan(Value* lval, Value* rval)
	{
		int result = do_cmp(lval, rval);
		if (result == -1)
		{
			Value* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			Value* bval = new BooleanValue(false);
			return bval;
		}
	}

	static Value* gtrthan(Value* lval, Value* rval)
	{
		int result = do_cmp(lval, rval);
		if (result == 1)
		{
			Value* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			Value* bval = new BooleanValue(false);
			return bval;
		}
	}

	static Value* leqthan(Value* lval, Value* rval)
	{
		int result = do_cmp(lval, rval);
		if ( result == -1 || result == 0)
		{
			Value* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			Value* bval = new BooleanValue(false);
			return bval;
		}
	}

	static Value* geqthan(Value* lval, Value* rval)
	{
		int result = do_cmp(lval, rval);
		if (result == 1 || result == 0)
		{
			Value* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			Value* bval = new BooleanValue(false);
			return bval;
		}
	}

	static Value* equalto(Value* lval, Value* rval)
	{
		int result = do_cmp(lval, rval);
		if (result == 0)
		{
			Value* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			Value* bval = new BooleanValue(false);
			return bval;
		}
	}

	static Value* neqto(Value* lval, Value* rval)
	{
		int result = do_cmp(lval, rval);
		if (result != 0)
		{
			Value* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			Value* bval = new BooleanValue(false);
			return bval;
		}
	}

	static Value* identto(Value* lval, Value* rval)
	{
		int result = 1;
		int ltype = lval->returnType();
		int rtype = rval->returnType();
		if ((ltype <= 2 && rtype <= 2) || (ltype == 6 && rtype == 6))
		{
			result = do_cmp(lval, rval);
		}
		if (result == 0)
		{
			Value* bval = new BooleanValue(true);
			return bval;
		}
		else
		{
			Value* bval = new BooleanValue(false);
			return bval;
		}
	}

	static Value* nidentto(Value* lval, Value* rval)
	{
		int result = 0;
		int ltype = lval->returnType();
		int rtype = rval->returnType();
		result = do_cmp(lval, rval);
		if (result != 0)
		{
			Value* bval = new BooleanValue(true);
			return bval;
		}
		else if (result == 0 && ((ltype <= 2 && rtype <=2) || (ltype == 6 && rtype == 6)))
		{
			Value* bval = new BooleanValue(false);
			return bval;
		}
		else
		{
			Value* bval = new BooleanValue(true);
			return bval;
		}
	}
};
