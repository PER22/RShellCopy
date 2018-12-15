#ifndef OUTPUTAPPEND_H
#define OUTPUTAPPEND_H

#include "Base.h"

class OutputAppend :public Base
{
private:
	Base* leftChild;
	Base* rightChild;
public:
	OutputAppend(Base*, Base*);
	~OutputAppend();
	virtual int execute();
	virtual void del();
};

#endif