#include "TreeBuilder.h"
#include "Execution.h"
#include "Test.h"
#include "Tokenizer.h"
#include "Semicolon.h"
#include "Pipe.h"
#include "Input.h"
#include "OutputOverride.h"
#include "OutputAppend.h"
#include "InputFile.h"
#include "OutputFile.h"
#include "iostream"
#include "sstream"
#include <string.h>
#include <stack>

TreeBuilder::TreeBuilder(std::string com){
	Tokenizer* tk = new Tokenizer(com);
	command = tk->tokenize();
}

Base* TreeBuilder::buildTree(){
//	std::cout<<"RPN:    ";
//	for(int i = 0; i < command.size(); i++){std::cout<<command[i]<<", ";}
//	std::cout<<"\n";
	for(int i = 0; i < command.size(); i++){
		if( this->isOperator(command[i]) || this->isRedirect(command[i])){
			//Operator, so pop 2 (if possible),
			//build, with 2 elements or NULLs as children
			//and re-push.
			//two+
			if(stackOfNodes.size() >= 2){ 
				Base* right = stackOfNodes.top();
				stackOfNodes.pop();
				Base* left = stackOfNodes.top();
				stackOfNodes.pop();
				Base* newCon = this->makeConnectors(command[i], left, right);
				stackOfNodes.push(newCon);
			}
			//one
			else if(stackOfNodes.size() == 1){
				Base* left = stackOfNodes.top();
				stackOfNodes.pop();
				Base* newCon = this->makeConnectors(command[i], left, NULL);
				stackOfNodes.push(newCon);
			}
			//none
			else{ 
				Base* newCon = this->makeConnectors(command[i], NULL, NULL);
			}
		}
		else{//Not an operator, so push onto stack.

			//-N = not file type, -I = input file type, -OO = output file type with override flag, -OA = output file type with append flag.
			std::string fileNodeType = "-N";
			if(i != command.size() - 1 && this->isRedirect(command[i+1])) 
				fileNodeType = getFileType(command[i+1]);

			Base* newNode = this->makeNodes(command[i], fileNodeType);
			stackOfNodes.push(newNode);	
		}
	}
	if(command.size() == 0){return NULL;}
	return stackOfNodes.top();
}

bool TreeBuilder::isOperator(std::string opOrNo){
	if( opOrNo.compare(";")== 0|| opOrNo.compare("&&") == 0 ||  opOrNo.compare("||") == 0 || opOrNo.compare("|") == 0){return true;}
	return false;
}
bool TreeBuilder::isRedirect(std::string opOrNo){
	if(opOrNo.compare("<") == 0 || opOrNo.compare(">") == 0 || opOrNo.compare(">>") == 0){return true;};
	return false;
}
std::string TreeBuilder::getFileType(std::string redirector){
	if(redirector == ">")
		return "-OO";	
	else if(redirector == ">>")
		return "-OA"; 
	else  
		return "-I";
}
Base* TreeBuilder::makeConnectors(std::string connect, Base* left, Base* right){
	Base* connector = NULL;
	if(connect == "&&"){connector = new AND(left, right);}
	else if(connect == ";"){connector = new Semicolon(left, right);}
	else if(connect == "||"){connector = new OR(left, right);}
	else if(connect == "|"){connector = new Pipe(left, right);}
	else if(connect == "<"){connector = new Input(left, right);}
	else if(connect == ">"){connector = new OutputOverride(left, right);}
	else if(connect == ">>"){connector = new OutputAppend(left, right);}
	return connector;
}
Base* TreeBuilder::makeNodes(std::string content, std::string fileNodeType){
	Base* newNode = NULL;
	if(content.find("test") == 0 && fileNodeType == "-N"){
		std::vector<std::string> singleArgs;
		std::string chunkOfString="";
		std::stringstream strstrm(content);
		char space = ' ';
		while(std::getline(strstrm, chunkOfString, space)){
			if(chunkOfString != ""){singleArgs.push_back(chunkOfString);}
		}
		if(singleArgs.size() == 2){
			newNode = new Test(singleArgs[1]);

		}
		else if(singleArgs.size() == 3){
			newNode = new Test(singleArgs[1], singleArgs[2]);}
		//Make a Test class	
	}
	else{
		//Make an Execution Object
		std::vector<std::string> singleArgs;
		std::string chunkOfString;
		std::stringstream strstrm(content);
		char space = ' ';
		while(std::getline(strstrm, chunkOfString, space)){
			if(chunkOfString != ""){singleArgs.push_back(chunkOfString);}
		}
		if(fileNodeType == "-N")
			newNode = new Execution(singleArgs);
		else if(fileNodeType == "-I")
			newNode = new InputFile(content);
		else 
			newNode = new OutputFile(content, (fileNodeType == "-OO") ? 'o': 'a');
	}
	return newNode;
}
