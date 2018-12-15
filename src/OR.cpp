#include "OR.h"
#include <iostream>
int OR::execute(){
//ensure left->right order, and exit early upon success of left.
	if(leftChild && rightChild){
		//std::cout<<"Beginning Or ..............\n";
		int left = leftChild->execute();
		if(left==0){ 
			//std::cout<<"Ending OR, left only.\n";
			return 0;
		}
		int right = rightChild->execute();
		if(right==0){
			//std::cout<<"Ending OR, Both.";
			return 0;
		}
	}
	else{std::cout<<"Syntax error: OR has null child.\n";}
	//std::cout<<"Ending OR, Neither.\n";
	return 1;
}
