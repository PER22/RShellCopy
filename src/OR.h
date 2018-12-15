#ifndef OR_H
#define OR_H

#include "Connector.h"
class OR : public Connector{
    public:
    	OR(Base* left, Base* right) : Connector(left,right){}
	virtual int execute();
};


#endif
