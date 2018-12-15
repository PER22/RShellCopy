#ifndef EXECUTION_H
#define EXECUTION_H
#include <vector>
#include "Base.h"
#include <string>
//This is the class that will handle commands.
//The only class that uses execvp and fork.
class Execution : public Base{
    private:
	    std::vector<std::string> command;	    
    public:
	Execution(std::vector<std::string> s){command = s;}
	~Execution();
	virtual int execute();
	virtual void del();
	void add_element(std::string);
};

#endif

