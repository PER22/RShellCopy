#include "InputFile.h"
#include <fstream>
InputFile::InputFile(std::string f){
	filename = f;
}

InputFile::~InputFile(){}

void InputFile::del(){this->~InputFile();}

int InputFile::execute(){
	std::ifstream file;
	file.open(this->filename);
	//if doesnt exist return a 1
	for( std::string line; getline(file, line ); ){
    		printf("%s\n", line.c_str());
    	}
	return 0;
}
