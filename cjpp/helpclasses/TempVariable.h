#ifndef TEMPVAR
#define TEMPVAR

using namespace std;
#include <iostream>

class TempVariable {
public:
	int num;
	TempVariable(int num) : num(num) {
	}
	std::ostream& operator<<(std::ostream &strm) {
  		return strm << ("tmp");
	}
	string toString() {
		return "tmp" + to_string(num);
	}
	
	
};

#endif
