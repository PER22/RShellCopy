#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "Connector.h"
class Semicolon : public Connector{
    public:
    	Semicolon(Base* left, Base* right) : Connector(left,right){};
	virtual int execute();
};


#endif



