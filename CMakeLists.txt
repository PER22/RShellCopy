CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(googletest)


ADD_EXECUTABLE(rshell	
	src/main.cpp
	src/Base.h
	src/Execution.h
	src/Execution.cpp
	src/Connector.h
	src/Connector.cpp
	src/AND.h
	src/AND.cpp
	src/OR.h
	src/OR.cpp
	src/TreeBuilder.h
	src/TreeBuilder.cpp
	src/Tokenizer.h
	src/Tokenizer.cpp
#	src/Container.h
#	src/Container.cpp
#	src/Subshell.h
#	src/Subshell.cpp
	src/Test.h
	src/Test.cpp
	src/Semicolon.h
	src/Semicolon.cpp
	src/Pipe.h
	src/Pipe.cpp
	src/InputFile.h
	src/InputFile.cpp
	src/OutputFile.h
	src/OutputFile.cpp
	src/OutputAppend.h
	src/OutputAppend.cpp
	src/OutputOverride.h
	src/OutputOverride.cpp
	src/Input.h
	src/Input.cpp
)
ADD_EXECUTABLE(test
	tests/test.cpp
	src/Base.h
	src/Execution.h
	src/Execution.cpp
	src/Connector.h
	src/Connector.cpp
	src/AND.h
	src/AND.cpp
	src/OR.h
	src/OR.cpp
	src/TreeBuilder.h
	src/TreeBuilder.cpp
	src/Tokenizer.h
	src/Tokenizer.cpp
#	src/Container.h
#	src/Container.cpp
#	src/Subshell.h
#	src/Subshell.cpp
	src/Test.h
	src/Test.cpp
	src/Semicolon.h
	src/Semicolon.cpp
	src/Pipe.h
	src/Pipe.cpp
	tests/testInjector.h

	src/InputFile.h
	src/InputFile.cpp
	src/OutputFile.h
	src/OutputFile.cpp
	src/OutputAppend.h
	src/OutputAppend.cpp
	src/OutputOverride.h
	src/OutputOverride.cpp
	src/Input.h
	src/Input.cpp
)
TARGET_LINK_LIBRARIES(test gtest)
