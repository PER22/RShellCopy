#include "Base.h"
#include "Execution.h"
#include "Connector.h"
#include "AND.h"
#include "OR.h"
#include "TreeBuilder.h"
#include "Tokenizer.h"
#include "Container.h"
#include "Test.h"
#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
void handleCommandLineArgs(int, char**);
void displayPrompt();
int main(int argv, char** argc){
	std::string rawInput = "";
	while(argv ==1){ 
		displayPrompt();//works
		std::getline(std::cin, rawInput);//works
		TreeBuilder tb(rawInput);//Constructs RPN crrectly
		Base* root = tb.buildTree();//unchecked
		if(root){root->execute();}
	}
	
	if(argv > 1){
		handleCommandLineArgs(argv, argc);
	}
	return 0;
}

void handleCommandLineArgs(int argv, char** argc){
	std::string cmdInput = "";
	for(int i = 1; i < argv; i++){
		cmdInput += (std::string)argc[i] + " ";	
	}
	TreeBuilder bldr(cmdInput);
	Base* root = bldr.buildTree();
	root->execute();
}

void displayPrompt(){
	char* userName;
	char hostName[100];
	userName = getlogin();
	int status = gethostname(hostName, 100);
	printf("%s@%s $: ",userName,hostName);
}
