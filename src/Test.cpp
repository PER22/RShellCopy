#include "Test.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
Test::Test(std::string op, std::string file){
	if(op != "-f" && op != "-d"){operationType = "-e";}
	else{operationType = op;}
	filePath = file;
}

Test::Test(std::string file){
	operationType  = "-e";
	filePath = file;
}

int Test::execute(){
	//Declare a struct for stat() to fill in
	struct stat fileStatus;
	//call stat and capture return val for error check
	int statStatus = stat(filePath.c_str(), &fileStatus);
	if(statStatus < 0){
		//perror("stat");
		std::cout<<"(False)\n";
		return 1;
	}
	//Based on what type
	switch(fileStatus.st_mode & S_IFMT){
	case S_IFDIR:
	//This logic was awkward, I wasnt sure if 
	// OO-style programming might have some best practice.
		if(operationType == "-d"){
			std::cout<<"(True)\n";
			return 0;
		}
		else if(operationType == "-e"){
			std::cout<<"(True)\n"; 
			return 0;
		}
		else{
			std::cout<<"(False)\n";
			return 1;
		}
		break;
	case S_IFREG:
		if(operationType == "-d"){
			std::cout<<"(False)\n";
			return 1;
		}
		else if(operationType == "-e"){
			std::cout<<"(True)\n"; 
			return 0;
		}
		else{
			std::cout<<"(True)\n";
			return 0;
		}
		break;
	default:
		return 1;
	}

}

void Test::del(){
	this->~Test();
}
