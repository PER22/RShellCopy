#ifndef TESTINJECTOR_H
#define TESTINJECTOR_H

#include "../src/Base.h"

class TestInjector : public Base {
    private:
	int val;
    public: 
    	TestInjector(int v){val = v;}
	int execute(){return val;}
	void del(){}
};

#endif
