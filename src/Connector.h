#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "Base.h"
class Connector : public Base{
    protected:
	Base* leftChild;
	Base* rightChild;
    public:
    	Connector(Base* left, Base* right){leftChild = left; rightChild = right;}
	~Connector();
	virtual int execute()=0;
	virtual void del();
	void addLeftChild(Base*);
	void addRightChild(Base*);
};


#endif
