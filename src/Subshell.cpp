#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <sstream>
#include "Subshell.h"

Subshell::Subshell(std::string text) : subCommand(text){}

int Subshell::execute(){
	//empty parentheses
	if(subCommand.size() == 0){return 0;}

	//split string on " "	
	std::string chunkOfSubCommand;
	std::vector<std::string> oneParsedSubCommand;
	std::stringstream subCommandStream(subCommand.c_str());
	//Tokenize wholeExpressions[i] by ' '.
	while(std::getline(subCommandStream, chunkOfSubCommand, ' ')){
		if(chunkOfSubCommand != ""){
			oneParsedSubCommand.push_back(chunkOfSubCommand);
		}
	}
	char* arguments[oneParsedSubCommand.size()+2];
	arguments[subCommand.size()+1] = NULL;
	std::string rs = "./rshell";
	arguments[0] = const_cast<char*>(rs.c_str());
	for(int i = 0; i < oneParsedSubCommand.size()+1; i++){
		arguments[i + 1] = const_cast<char*>(oneParsedSubCommand[i].c_str());
	}

	int status;
	pid_t procID = fork();
	if(procID < 0){
		perror("Failure to fork to process sub Command\n"); 
		exit(1);
	}
	else if( procID == 0 ){
		int execVal = execvp(*arguments, arguments);
		if(execVal < 0){
			perror(std::string(std::string(*arguments) + ": command not found\n").c_str());
			exit(1);
		}
	}
	else{
		while(wait(&status) != procID){;}
	}
	return status;
}

void Subshell::del(){this->~Subshell();}

