#include "OutputOverride.h"
#include <cstdlib>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
OutputOverride::~OutputOverride() {}

OutputOverride::OutputOverride(Base* leftChild, Base* rightChild)
{
	this->leftChild = leftChild;
	this->rightChild = rightChild;
}

int OutputOverride::execute() {

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
	if(pid == 0){
		//child
		close(1);
		close(fd[0]);
		if(dup(fd[1]) < 0){exit(1);}

		int leftStat = leftChild->execute();
		//now output of leftChild should be stored in pipe
		exit(leftStat);
	}
	else{

		//parent
		//Wait for child to die
		while( wait(&childStatus) != pid ){;}
		if(childStatus != 0){
			//left side failed, do not pipe.
			//close pipe
			close(fd[0]);
			close(fd[1]);
			return 1;
		}
		else{
			//leftSide succeeded
			close(0);
			close(fd[1]);
			//dup() so that input comes from "read" end of pipe
			dup(fd[0]);
			//execute and input should be read from pipe rather than stdin
			int rightStat = rightChild->execute();
			//we can now close the pipe
			close(fd[0]);
			dup2(stdinSaved,0);
			dup2(stdoutSaved,1);
		}
	}
}

void OutputOverride::del() {
	if (leftChild) { leftChild->del(); }
	if (rightChild) { rightChild->del(); }
	this->~OutputOverride();
}
