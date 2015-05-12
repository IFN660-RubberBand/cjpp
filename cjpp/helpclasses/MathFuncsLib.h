#include <string>
#include <sstream>

using namespace std;

class MathFuncs{
public:
	
	/*
	 * Deprecated
	 */
	static double Add(double lval, double rval){
		return lval + rval;
	};

	/*
	 * Deprecated
	 */
	static string AddString(string lval, string rval){
		return lval + rval;
	};

	/*
	 * Deprecated
	 */
	template<typename L, typename R>
	static auto AddObject(L lval, R rval) -> decltype(lval + rval){
		cout << lval << ":" << rval << endl;
		return lval + rval;
	};

	template<typename L, typename R>
	static auto do_add(L lval, R rval, false_type){
		return lval + rval;
	}

	template<typename L, typename R>
	static string do_add(L lval, R rval, true_type){
		ostringstream oss;
		oss << lval << rval;
		return oss.str();
	}

	/*
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
};
