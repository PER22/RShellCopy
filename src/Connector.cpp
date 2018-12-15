#include "Connector.h"
#include <stdio.h>

Connector::~Connector(){
}
//Connector implements del, because deletion 
//will always want to handle both children 
//and then itself.
void Connector::del(){
	if(leftChild){	
		leftChild->del();
	}
	if(rightChild){	
		rightChild->del();
	}
	this->~Connector();
}
