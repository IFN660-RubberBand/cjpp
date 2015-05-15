#include <string>
#include <sstream>
#include "value.h"

using namespace std;

class MathFuncs: public Value{
public:
    static auto addV(Value* lval, Value* rval){
        
        
        
        return 0;
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
    
	/* \deprecated { Uses template instead of objects }
	* Comparators
	*/
	template<typename L, typename R>
	static auto do_cmp(L lval, R rval, true_type)
	{
		// need conversion if lval or rval are of type char*

		float flval = atof(lval);
		float frval = rval;

		float sign = flval - frval;
		if (sign > 0)
			return 1;
		else if (sign < 0)
			return -1;
		else
			return 0;
	}	

	template<typename L, typename R>
	static auto do_cmp(L lval, R rval, false_type)
	{
		float sign = lval - rval;
		if (sign > 0)
			return 1;
		else if (sign < 0)
			return -1;
		else
			return 0;
	}

	template<typename L, typename R>
	static auto lssthan(L lval, R rval)
	{
		using dispatch_type = integral_constant<
			bool, 
			is_convertible<L, string>{}
			|| is_convertible<R, string>{} >;
	int result = do_cmp(lval, rval, dispatch_type());
	if (result == -1)
		return true;
	else
		return false;
	}

	template<typename L, typename R>
	static auto gtrthan(L lval, R rval)
	{
		using dispatch_type = integral_constant<
			bool, 
			is_convertible<L, string>{}
			|| is_convertible<R, string>{} >;
	int result = do_cmp(lval, rval, dispatch_type());
	if (result == 1)
		return true;
	else
		return false;
	}

	template<typename L, typename R>
	static auto leqthan(L lval, R rval)
	{
		using dispatch_type = integral_constant<
			bool, 
			is_convertible<L, string>{}
			|| is_convertible<R, string>{} >;
	int result = do_cmp(lval, rval, dispatch_type());
	if ((result == -1) || (result == 0))
		return true;
	else
		return false;
	}

	template<typename L, typename R>
	static auto geqthan(L lval, R rval)
	{
		using dispatch_type = integral_constant<
			bool, 
			is_convertible<L, string>{}
			|| is_convertible<R, string>{} >;
	int result = do_cmp(lval, rval, dispatch_type());
	if ((result == 1) || (result == 0))
		return true;
	else
		return false;
	}

	template<typename L, typename R>
	static auto equalto(L lval, R rval)
	{
		using dispatch_type = integral_constant<
			bool, 
			is_convertible<L, string>{}
			|| is_convertible<R, string>{} >;
	int result = do_cmp(lval, rval, dispatch_type());
	if (result == 0)
		return true;
	else
		return false;
	}

	template<typename L, typename R>
	static auto neqto(L lval, R rval)
	{
		using dispatch_type = integral_constant<
			bool, 
			is_convertible<L, string>{}
			|| is_convertible<R, string>{} >;
	int result = do_cmp(lval, rval, dispatch_type());
	if (result != 0)
		return true;
	else
		return false;
	}
};
