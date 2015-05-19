#ifndef JMPLABEL
#define JMPLABEL

using namespace std;
#include <iostream>

class JumpLabel {
public:
	int num;
	JumpLabel(int num) : num(num) {
	}

	string toString() const {
		return "JmpLabel" + to_string(num);
	}
	
	
};

#endif
