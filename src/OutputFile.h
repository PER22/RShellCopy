#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H
#include "Base.h"
#include <string>
class OutputFile : public Base{
    private:
	std::string filename;
	char mode;
    public:
    	OutputFile(std::string f, char m);
	~OutputFile();
	virtual int execute();
	virtual void del();

};
#endif
