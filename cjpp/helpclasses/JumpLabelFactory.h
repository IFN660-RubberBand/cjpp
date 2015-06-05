#ifndef JMPLABELFAC
#define JMPLABELFAC

#include <iostream>
#include "JumpLabel.h"
using namespace std;

class JumpLabelFactory {
private:
	static int maxvar;
	static int current;
public:
	static JumpLabel* getLabel() {
		JumpLabel* t = new JumpLabel(current);
		if(current == maxvar) {
			++maxvar;
		}
		current++;
		return t;
	}
	static void reset() {
		current = 0;
	}
	
};

#endif
