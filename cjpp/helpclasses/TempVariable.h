#ifndef TEMPVAR
#define TEMPVAR

using namespace std;
#include <iostream>

class TempVariable {
public:
	int num;
	TempVariable(int num) : num(num) {
	}

	string toString() const {
		return "tmp" + to_string(num);
	}
	
	
};

#endif
