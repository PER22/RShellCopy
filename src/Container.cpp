#include "Base.h"
#include "Container.h"
#include "Tokenizer.h"
#include "TreeBuilder.h"
#include <iostream>
#include <string>
#include <vector>

Container::Container(Tokenizer* tokenizer, TreeBuilder* treebuilder) {
	this->tokenizer = tokenizer;
	this->treebuilder = treebuilder;
	parsedExpressions = tokenizer->tokenize();
}


void Container::executeAll() {
	for (int i = 0; i < commandTrees.size(); i++) {
		commandTrees[i]->execute();
	}
}

void Container::deleteAll() {
	for (int i = 0; i < commandTrees.size(); i++) {
		commandTrees[i]->del();
	}
}
