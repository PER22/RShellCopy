#include "OutputFile.h"
#include <fstream>
#include <iostream>
OutputFile::OutputFile(std::string f, char m){
	filename = f;

	m != 'a'? m = 'o' : m = 'a';
}

OutputFile::~OutputFile(){}

void OutputFile::del(){
	this->~OutputFile();
}

int OutputFile::execute(){
	std::ofstream file;
	if(mode == 'a'){
		file.open(filename,std::ofstream::app);
	}
	else{
		file.open(filename, std::ofstream::trunc);
	}
	while (!std::cin.eof()){
	   std:: string line;
	    std::getline(std::cin, line);

	    if (std::cin.fail())
	    {
		//error
		break;
	    }

	    file<<line;
	}	
	std::cin.clear();
	file.close();

}
