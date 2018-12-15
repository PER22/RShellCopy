#include "Tokenizer.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstring>
#include <stack>
#include <queue>


std::vector<std::string> Tokenizer::tokenize() {

	//Remove comment from userCommand
	stripComment();

	//Add set of parenthesis.
	userCommand = "(" + userCommand + ")";

	////Check for valid connectors. (|| , &&)
	//if (!isConnectorValid()) {
	//	std::cout << "Invalid syntax\n";
	//	return tokenizedUserCommand;
	//}

	//Validate balanced parenthesis
	if (!isParanthesisBalanced()) {
		std::cout << "Unbalanced parenthesis\n";
		return tokenizedUserCommand;
	}

	//Remove unecessary semicolons
	removeUnecessarySemicolons();

	//Fix string to add spaces where connectors occur so tokenization works appropriately.
	findAndReplace(userCommand, "&&", " && ");
	findAndReplace(userCommand, "|", " | ");
	findAndReplace(userCommand, "|  |", "||");
	findAndReplace(userCommand, "<", " < ");
	findAndReplace(userCommand, ">", " > ");
	findAndReplace(userCommand, ">  >", ">>");
	findAndReplace(userCommand, ";", " ; ");
	findAndReplace(userCommand, "(", " ( ");
	findAndReplace(userCommand, ")", " ) ");
	findAndReplace(userCommand, "[", " test ");
	findAndReplace(userCommand, "]", "");


	//Tokenize userCommand on ' '
	tokenizeUserCommand(userCommand, ' ');

	//Convert tokens to reverse polar form.
	std::queue<std::string> queueRPN = convertToReversePolar();

	//Convert queue to string
	queueToVector(queueRPN);

	return tokenizedUserCommand;
}

enum color { ANDOR, LEFTPAREN, SEMICOLON, RIGHTPAREN };

std::queue<std::string> Tokenizer::convertToReversePolar() {
	bool isParameter = false;
	std::stack<std::string> stackOperands;
	std::queue<std::string> queueRPN;
	for (unsigned i = 1; i < tokenizedUserCommand.size() - 1; i++) {

		std::string currToken = tokenizedUserCommand[i];
		if (!isOperator(currToken)) {
			currToken = (isParameter) ? "~" + currToken : currToken;
			//Push non-operands directly into queue
			queueRPN.push(currToken);
			isParameter = true;
		}
		else {
			isParameter = false;
			int currOperator = getOperatorPrecedence(currToken);
			int stackOperator = (stackOperands.empty()) ? -1 : getOperatorPrecedence(stackOperands.top());

			if (currOperator == RIGHTPAREN) {
				//Push operators from stack into queue until '(' is found
				for (unsigned i = 0; i < stackOperands.size(); i++) {

					stackOperator = getOperatorPrecedence(stackOperands.top());
					if (stackOperator == LEFTPAREN) {
						stackOperands.pop();
						break;
					}
					else {
						//Push operand into queue.
						queueRPN.push(stackOperands.top());
						stackOperands.pop();
					}

				}
			}
			else if (currOperator <= stackOperator && !stackOperands.empty() && stackOperator != LEFTPAREN) {
				queueRPN.push(stackOperands.top());
				stackOperands.pop();
				stackOperands.push(currToken);
			}
			else {
				stackOperands.push(currToken);
			}
		}
	}

	//Push all operands left on stack to queue.
	while (!stackOperands.empty()) {
		std::string currOp = stackOperands.top();
		int currOpPrecedence = getOperatorPrecedence(currOp);
		if (currOpPrecedence != LEFTPAREN)
			queueRPN.push(currOp);
		stackOperands.pop();
	}
	return queueRPN;
}

int Tokenizer::getOperatorPrecedence(std::string operand) {
	int precedence = 0;

	if (operand == ")")
		precedence = 3;
	//else if (operand == ";")
	//	precedence = 2;
	else if (operand == "(")
		precedence = 1;
	else if (operand == "&&" || operand == "||" || operand == ";" ||
			 operand == "|" || operand == "<" || operand == ">" || operand == ">>")
		precedence = 0;

	return precedence;
}

bool Tokenizer::isOperator(std::string token) {
	std::vector<std::string> operators{ "||", "&&", ";", "(", ")", "|", "<", ">", ">>" };
	for (unsigned i = 0; i < operators.size(); i++) {
		if (token == operators[i])
			return true;
	}
	return false;
}

bool Tokenizer::isConnectorValid() {
	bool validConnector = true;
	for (unsigned i = 0; i < userCommand.length(); i++) {
		if ((userCommand[i] == '&') && i != userCommand.length() - 1) {
			validConnector = (userCommand[i] == userCommand[i + 1]) ? true : false;
			if (!validConnector) break;
			i += 1;
		}
		else if (userCommand[i] == ';' && i != userCommand.length() - 1) {
			validConnector = (userCommand[i] == userCommand[i + 1]) ? false : true;
			if (!validConnector) break;
			i += 1;
		}
	}
	return validConnector;
}

bool Tokenizer::isParanthesisBalanced()
{
	char currChar;
	std::stack<char> balanceStack;

	for (unsigned i = 0; i < userCommand.length(); i++)
	{
		if (userCommand[i] == '(' || userCommand[i] == '[')
		{
			balanceStack.push(userCommand[i]);
			continue;
		}

		if (balanceStack.empty())
			return false;

		if (userCommand[i] == ')') {
			currChar = balanceStack.top();
			balanceStack.pop();
			if (currChar == '[')
				return false;
		}
		else if (userCommand[i] == ']') {
			currChar = balanceStack.top();
			balanceStack.pop();
			if (currChar == '(')
				return false;
		}
	}
	return balanceStack.empty();
}

void Tokenizer::tokenizeUserCommand(std::string command, char splitOn) {
	std::string chunkOfStream;
	std::stringstream commandStream(command);
	tokenizedUserCommand.clear();
	while (std::getline(commandStream, chunkOfStream, splitOn)) {
		if (chunkOfStream != "") {
			tokenizedUserCommand.push_back(findAndReplace(chunkOfStream, "~", " "));
		}
	}
}

void Tokenizer::stripComment() {
	std::size_t cmnt = userCommand.find("#");
	if (cmnt != 0)
		userCommand = userCommand.substr(0, cmnt);
}

void Tokenizer::removeUnecessarySemicolons() {
	int lastCharIndx = 0;
	std::string lastChar;
	for (unsigned i = 0; i < userCommand.length(); i++) {
		if (lastChar + userCommand[i] == ";)") {
			std::string badSemiSubStr = userCommand.substr(0, i + 1);
			std::string correctSubStr = userCommand.substr(0, lastCharIndx) + ")";
			findAndReplace(userCommand, badSemiSubStr, correctSubStr);
			lastChar = ' ';
		}
		if (userCommand[i] != ' ') {
			lastChar = userCommand[i];
			lastCharIndx = i;
		}
	}
}

void Tokenizer::queueToVector(std::queue<std::string> rpnQueue) {
	unsigned queueIndx = rpnQueue.size();
	for (unsigned i = 0; i < queueIndx; i++) {

		if (rpnQueue.front().substr(0, 1) == "~")
			rpnCommandString = rpnCommandString.substr(0, rpnCommandString.length() - 1) + rpnQueue.front() + " ";
		else if (!isOperator(rpnQueue.front()))
			rpnCommandString += rpnQueue.front() + " ";
		else
			rpnCommandString += " " + rpnQueue.front() + " ";
		rpnQueue.pop();

	}

	tokenizeUserCommand(rpnCommandString, ' ');
}

int Tokenizer::getStringOccurance(std::string originalString, std::string searchFor) {
	int occuranceCounter = 0;
	for (unsigned i = 0; i < originalString.size(); i++)
	{
		std::string subStr = originalString.substr(i, searchFor.length());
		if (std::strcmp(subStr.c_str(), searchFor.c_str()) == 0)
			occuranceCounter++;
	}
	return	occuranceCounter;
}

std::string Tokenizer::findAndReplace(std::string& originalString, const std::string& toReplace, const std::string& replaceWith)
{
	unsigned occurances = getStringOccurance(originalString, toReplace);
	unsigned position = 0;
	for (unsigned i = 0; i < occurances && position < originalString.length(); i++) {
		position += originalString.substr(position, originalString.length()).find(toReplace);
		originalString.replace(position, toReplace.length(), replaceWith);
		position += replaceWith.length() - toReplace.length();
	}
	return originalString;
}