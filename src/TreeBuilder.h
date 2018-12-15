#ifndef TREEBUILDER_H
#define TREEBUILDER_H

#include "Base.h"
#include "Execution.h"
#include "AND.h"
#include "OR.h"
#include <vector>
#include <string>
#include <stack>

class TreeBuilder{
	private:
		std::vector<std::string> command;
		std::stack<Base*> stackOfNodes;
	
		bool isOperator(std::string opOrNo);
		bool isRedirect(std::string opOrNo);
		std::string getFileType(std::string redirector);
		Base* makeConnectors(std::string connect, Base* left, Base* right);
		Base* makeNodes(std::string content, std::string fileNodeType);
	public:
	
	TreeBuilder(std::string com);
	Base* buildTree();
};

#endif
