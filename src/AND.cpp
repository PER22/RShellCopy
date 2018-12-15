#include "AND.h"
#include <iostream>
int AND::execute(){
//ensure left -> right execution
	if(leftChild && rightChild){
		int left = leftChild->execute();
		if(left == 0){//if left worked, try right now.
			int right = rightChild->execute();
			if(right == 0){
				//We know they both worked, return success.
				return 0;
			}
		}
	}
	else{std::cout<<"Syntax Error: AND has null child.\n"; }
	return 1;
}
