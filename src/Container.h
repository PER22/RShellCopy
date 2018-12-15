#ifndef CONTAINER_H
#define CONTAINER_H

#include "Base.h"
#include "Tokenizer.h"
#include "TreeBuilder.h"
#include <vector>


class Container {
private:
	Tokenizer* tokenizer;
	TreeBuilder* treebuilder;
	std::string rpnCommandString;
	std::vector<Base*> commandTrees;
	std::vector<std::string> parsedExpressions;
public:
	// Constructors 
	Container(Tokenizer*, TreeBuilder*);

	// Functions
	void executeAll();
	void deleteAll();
};

#endif