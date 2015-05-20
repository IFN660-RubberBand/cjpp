#include <string>
#include <sstream>
#include "value.h"
//#include "Values.h"

using namespace std;

class MathFuncs{
public:
    /*
     Testing method
     */
    static Value* addV(Value* lval, Value* rval){
        if(IntegerValue* vlval = dynamic_cast<IntegerValue*>(lval)){
            return vlval;
        }
        
        return new UndefinedValue();
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

	static int do_cmp(Value* lval, Value* rval, int ltype, int rtype)
	{
		switch(ltype) {
			case 1:
				if ((rtype == 1) || (rtype == 3))
					return comparenumbers(lval, rval);
				break;
			case 2:
				break;
			case 3:
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
	}

	static int comparenumbers(Value* lval, Value* rval)
	{
		float sign = lval - rval;
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

	static bool lssthan(Value* lval, Value* rval)
	{
	int ltype = lval->returnType();
	int rtype = rval->returnType();
	int result = do_cmp(lval, rval, ltype, rtype);
	if (result == -1)
		return true;
	else
		return false;
	}

	static bool gtrthan(Value* lval, Value* rval)
	{
	int ltype = lval->returnType();
	int rtype = rval->returnType();
	int result = do_cmp(lval, rval, ltype, rtype);
	if (result == 1)
		return true;
	else
		return false;
	}
};
