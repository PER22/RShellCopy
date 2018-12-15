#ifndef AND_H
#define AND_H

#include "Connector.h"
class AND : public Connector{
    public:
	AND(Base* left, Base* right) : Connector(left, right){}
	virtual int execute();
};

#endif
