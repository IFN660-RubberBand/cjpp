#ifndef TEMPVARFAC
#define TEMPVARFAC

using namespace std;
#include <iostream>
#include "TempVariable.h"

class TempVariableFactory {
private:
	static int maxvar;
	static int current;
public:
	static TempVariable* getTemp() {
		TempVariable* t = new TempVariable(current);
		if(current == maxvar) {
			++maxvar;
			cout << "Variable* " << t->toString() << ";" << endl;
		}
		current++;
		return t;
	}
	static void reset() {
		current = 0;
	}
	
};

#endif
