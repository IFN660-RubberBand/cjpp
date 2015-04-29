#include <stdint.h>


class Value {
};


class IntegerValue : public Value {
public:
	int32_t v;
	IntegerValue(int32_t v) : v(v)
	{}
	
};
