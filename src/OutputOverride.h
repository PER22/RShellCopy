#ifndef OUTPUTOVERRIDE_H
#define OUTPUTOVERRIDE_H

#include "Base.h"

class OutputOverride :public Base{
	private:
		Base* leftChild;
		Base* rightChild;
	public:
		OutputOverride(Base*, Base*);
		~OutputOverride();
		virtual int execute();
		virtual void del();
};

#endif
