#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <string>
#include "../src/Base.h"
#include "../src/Execution.h"
#include "../src/Connector.h"
#include "../src/AND.h"
#include "../src/OR.h"
#include "../src/Semicolon.h"
#include "../src/TreeBuilder.h"
#include "../src/Tokenizer.h"
#include "../src/Pipe.h"

#include "testInjector.h"


TEST(AND_Tests, and1){
	Base* left = new TestInjector(0);
	Base* right = new TestInjector(0);
	AND andy(left,right);
	EXPECT_EQ(andy.execute(), 0);
}


TEST(AND_Tests, and2){
	Base* left = new TestInjector(0);
	Base* right = new TestInjector(1);
	AND andy(left,right);
	EXPECT_EQ(andy.execute(), 1);
}

TEST(AND_Tests, and3){
	Base* left = new TestInjector(1);
	Base* right = new TestInjector(0);
	AND andy(left,right);
	EXPECT_EQ(andy.execute(), 1);
}

TEST(AND_Tests, and4){
	Base* left = new TestInjector(1);
	Base* right = new TestInjector(1);
	AND andy(left,right);
	EXPECT_EQ(andy.execute(), 1);
}
//OR TEST

TEST(OR_Tests, or1){
	Base* left = new TestInjector(0);
	Base* right = new TestInjector(0);
	OR orNode(left,right);
	EXPECT_EQ(orNode.execute(), 0);
}
TEST(OR_Tests, or2){
	Base* left = new TestInjector(0);
	Base* right = new TestInjector(1);
	OR orNode(left,right);
	EXPECT_EQ(orNode.execute(), 0);
}
TEST(OR_Tests, or3){
	Base* left = new TestInjector(1);
	Base* right = new TestInjector(0);
	OR orNode(left,right);
	EXPECT_EQ(orNode.execute(), 0);
}
TEST(OR_Tests, or4){
	Base* left = new TestInjector(1);
	Base* right = new TestInjector(1);
	OR orNode(left,right);
	EXPECT_EQ(orNode.execute(), 1);
}
//Semicolon Tests


TEST(Semicolon_Tests, semi1){
	Base* left = new TestInjector(0);
	Base* right = new TestInjector(0);
	Semicolon semiNode(left,right);
	EXPECT_EQ(semiNode.execute(), 0);
}
TEST(Semicolon_Tests, semi2){
	Base* left = new TestInjector(0);
	Base* right = new TestInjector(1);
	Semicolon semiNode(left,right);
	EXPECT_EQ(semiNode.execute(), 1);
}
TEST(Semicolon_Tests, semi3){
	Base* left = new TestInjector(1);
	Base* right = new TestInjector(0);
	Semicolon semiNode(left,right);
	EXPECT_EQ(semiNode.execute(), 0);
}
TEST(Semicolon_Tests, semi4){
	Base* left = new TestInjector(1);
	Base* right = new TestInjector(1);
	Semicolon semiNode(left,right);
	EXPECT_EQ(semiNode.execute(), 1);
}
TEST(Semicolon_Tests, semi5){
	Base* left = new TestInjector(1);
	Base* right = NULL;
	Semicolon semiNode(left,right);
	EXPECT_EQ(semiNode.execute(), 1);
}

TEST(Semicolon_Tests, semi6){
	Base* left = new TestInjector(0);
	Base* right = NULL;
	Semicolon semiNode(left,right);
	EXPECT_EQ(semiNode.execute(), 0);
}



TEST(Tokenizer_Tests, toke1){
	std::vector<std::string> output= {"echo left", "echo right", "&&"};
	std::string input = "echo left && echo right";
	Tokenizer tk(input);
	std::vector<std::string> newVec = tk.tokenize();	
	EXPECT_EQ(output.size(), newVec.size());
	for(int i = 0; i < output.size(); i++){
		EXPECT_TRUE(output[i] == newVec[i]);
	}

}


TEST(Tokenizer_Tests, toke2){
	std::vector<std::string> output= {"echo 1", "echo 2", "||", "echo 3", ";"};
	std::string input = "echo 1 || echo 2; echo 3";
	Tokenizer tk(input);
	std::vector<std::string> newVec = tk.tokenize();	
	EXPECT_EQ(output.size(), newVec.size());
	for(int i = 0; i < output.size(); i++){
		EXPECT_TRUE(output[i] == newVec[i]);
	}

}

TEST(Tokenizer_Tests, toke3){
	std::vector<std::string> output= {"echo 1", "echo 2", "||", "echo 3", "||"};
	std::string input = "(echo 1 || echo 2) || echo 3";
	Tokenizer tk(input);
	std::vector<std::string> newVec = tk.tokenize();	
	EXPECT_EQ(output.size(), newVec.size());
	for(int i = 0; i < output.size(); i++){
		EXPECT_TRUE(output[i] == newVec[i]);
	}

}

TEST(PipeTest, pipetest1){
//This was just to test that it would not crash
	std::vector<std::string> leftComs;
	std::vector<std::string> rightComs;
	//left command will be: echo abcdefg
	leftComs.push_back("cat");
	leftComs.push_back("startFile");
	//right command will be: tr a-z A-z
	rightComs.push_back("tr");
	rightComs.push_back("a-z");
	rightComs.push_back("A-Z");
	Base* leftExec = new Execution(leftComs);
	Base* rightExec = new Execution(rightComs);
	Pipe* p = new Pipe(leftExec, rightExec);
	//third command will be: tee newFile1
	std::vector<std::string> thirdComs;
	thirdComs.push_back("tee");
	thirdComs.push_back("newFile1");
	Base* tee = new Execution(thirdComs);
	Pipe* p2 = new Pipe(p, tee);

	//fourth command will be: tr A-Z a-z
	std::vector<std::string> fourthComs;
	fourthComs.push_back("tr");
	fourthComs.push_back("A-Z");
	fourthComs.push_back("a-z");
	Base* tr = new Execution(fourthComs);
	Pipe* p3 = new Pipe(p2, tr);

	//fifthCommand will be : tee newFile2
	std::vector<std::string> fifthComs;
	fifthComs.push_back("tee");
	fifthComs.push_back("newFile2");
	Base* tee2 = new Execution(fifthComs);
	Pipe* p4 = new Pipe(p3, tee2);
	
	p4->execute();


}

TEST(PipeTest, pipe2){
	std::vector<std::string> leftComs;
	std::vector<std::string> rightComs;
	//left command will be: cat startFile
	leftComs.push_back("cat");
	leftComs.push_back("startFile");
	//right command will be: tee endFile
	rightComs.push_back("tee");
	rightComs.push_back("endFile");
	Base* leftExec = new Execution(leftComs);
	Base* rightExec = new Execution(rightComs);
	Pipe* p = new Pipe(leftExec, rightExec);
	p->execute();
}
int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	std::cout<<"These are the single element Tests. The system tests are in bashTest.sh in the root directory"<<std::endl;
	return RUN_ALL_TESTS();
}

