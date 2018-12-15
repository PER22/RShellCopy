#include "Execution.h"
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

Execution::~Execution(){}

void Execution::del(){
	this->~Execution();
}

int Execution::execute(){
	//std::cout<<"Begiining Execution....................\n";
//No need to execute empty commands
	if (command.size() == 0){return 0;}
	if(command.size() == 1){
		if(command[0] == "exit"){
			exit(0);
		}
	
	}
//Make a NULL terminated char* array which will be '\0' terminated by .c_str()
	char* arguments[command.size()+1];
	arguments[command.size()] = NULL;
//Fill array with each string's C-String
	for(int i  = 0; i < command.size(); i++){
		arguments[i] = (char*)command[i].c_str();
	}
//make variable for status variable needed by wait()	
	int status;
	pid_t procID = fork();//fork child
	if(procID < 0){perror("Failure to fork.\n"); exit(1);}
	else if(procID == 0){//if in child proc
		int execVal = execvp(*arguments, arguments);
		if (execVal < 0){
			perror(*arguments);
			exit(1);//return fail, kill thread
		}
	}

	else{//else in arent proc
		while(wait(&status) != procID){;}
	}
	//std::cout<<"Ending Execution.\n";
	return status;
}


void Execution::add_element(std::string s){
	command.push_back(s);
}

