#ifndef TEST_H
#define TEST_H
#include "Base.h"
#include <string>
#include <vector> 


class Test : public Base{
    private:
	std::string operationType;
	std::string filePath;
    public:
    	Test(std::string op, std::string file);
	Test(std::string file);
	~Test(){}
	int execute();
	void del();
};


#endif
