#ifndef INPUT_H
#define INPUT_H
#include "Base.h"

class Input : public Base{
    private:
   	Base* leftChild;
	Base* rightChild;
    public:
    	Input(Base* l, Base* r);
	~Input();
	virtual int execute();
	virtual void del();
};
#endif
