#ifndef INPUTFILE_H
#define INPUTFILE_H
#include "Base.h"
#include <string>
class InputFile : public Base{
    private:
    	std::string filename;
    public:
    	InputFile(std::string f);
	~InputFile();
	virtual int execute();
	virtual void del();
};
#endif
