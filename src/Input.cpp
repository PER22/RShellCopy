#include "Input.h"
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

Input::Input(Base* l, Base* r){
	leftChild = l;
	rightChild = r;
}

Input::~Input(){}

void Input::del(){
	if(leftChild){leftChild->del();}
	if(rightChild){rightChild->del();}
	this->~Input();
}

int Input::execute(){

	//save stdin/stdout fd's using default fd values
	int stdinSaved = dup(0);
	int stdoutSaved = dup(1);

	//variables for process ID, the filedescriptors of the pipe, 
	//and the exit status of the child process
	pid_t pid;
	int fd[2];
	int childStatus;

        if(pipe(fd) < 0){exit(1);}
	
	
	


	pid = fork();
	if(pid < 0){exit(1);}
	if(!pid){
	//child:
		//change stdout to pipeOut and close pipeIn
		close(1);
		dup(fd[1]);
		close(fd[0]);
		int rightStat = rightChild->execute();
		exit(rightStat);
	}
	else{

		while( wait(&childStatus) != pid ){;}
		if(childStatus != 0){
			close(fd[0]);
			close(fd[1]);
			dup2(stdinSaved,0);
			dup2(stdoutSaved,1);
			return 1;
		}
		else{
			close(0);
			close(fd[1]);
			dup(fd[0]);

			int leftStat = leftChild->execute();
			close(fd[0]);

			dup2(stdinSaved,0);
			dup2(stdoutSaved,1);
			return leftStat;
		}	
	
	}
}
