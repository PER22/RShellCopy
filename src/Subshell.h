#ifndef SUBSHELL_H
#define SUBSHELL_H

#include "Base.h"
#include <string>

class Subshell : public Base{
    private:
	std::string subCommand;
    public:
	Subshell(std::string);
	~Subshell(){}
	int execute();
	void del();
};




#endif
