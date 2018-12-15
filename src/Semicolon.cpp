#include "Semicolon.h"
#include <iostream>
int Semicolon::execute(){
//Semi colon must execute all/both existing children.
//It returns the success value returned by its last command.
	int val = 0;
	if(leftChild){
		val = leftChild->execute();
	}
	if(rightChild){
		val = rightChild->execute();
	}
	return val;

}
