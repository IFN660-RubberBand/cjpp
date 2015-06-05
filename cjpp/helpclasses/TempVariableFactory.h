#ifndef TEMPVARFAC
#define TEMPVARFAC

#include <iostream>
#include "TempVariable.h"

using namespace std;

class TempVariableFactory {
private:
	static int maxvar;
	static int current;
public:
	static TempVariable* getTemp() {
		TempVariable* t = new TempVariable(current);
		if(current == maxvar) {
			++maxvar;
			cout << "Value* " << t->toString() << ";" << endl;
		}
		current++;
		return t;
	}
	static void reset() {
		current = 0;
		maxvar = 0;
	}
	static void clear() {
		current = 0;
	}
};

#endif
