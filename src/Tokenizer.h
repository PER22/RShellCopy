#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Base.h"
#include <vector>
#include <string>
#include <queue>
//This was redone to use a stack-based algorithm
//Shunting Yard to put the tokens into RPN, which
//is easy to buiild using the TreeBuilder that will 
//own this object.

class Tokenizer {
private:
	void tokenizeUserCommand(std::string, char);
	std::queue<std::string> convertToReversePolar();

	void stripComment();
	bool isConnectorValid();
	bool isParanthesisBalanced();
	bool isOperator(std::string);
	void removeUnecessarySemicolons();
	int getOperatorPrecedence(std::string);	
	void queueToVector(std::queue<std::string>);
	int getStringOccurance(std::string originalString, 
		std::string searchFor);
	std::string findAndReplace(std::string& originalString,
		const std::string& toReplace, 
		const std::string& replaceWith);
protected:
	std::string userCommand;
	std::vector<std::string> tokenizedUserCommand;
	std::string rpnCommandString;
public:

	Tokenizer(std::string userCommand) { this->userCommand = userCommand; };

	std::vector<std::string> tokenize();
};

#endif
