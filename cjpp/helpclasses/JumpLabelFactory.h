#ifndef JMPLABELFAC
#define JMPLABELFAC

using namespace std;
#include <iostream>
#include "JumpLabel.h"

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
