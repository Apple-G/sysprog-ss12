#pragma once

#include <fstream>
#include <iostream>
#include "Token.h"
#include "CharOperation.h"

class BufferIO
{
private:
	//Buffer in
	unsigned int bufferSize;
	char *buffer;
	int bufferPosition;
	void getNewBuffer();
	void ungetCharOnce();

	std::ifstream document;
	char * inFile;
	int documentLength;
	int documentPosition;

	int line;
	int columnSize;
	int * column;	
	void extendColumnArray();

	bool endOfFile;


	//Buffer out
	unsigned int outBufferSize;
	char *outBuffer;
	int outBufferPosition;
	void extendOutBuffer();


	std::ofstream write;
	char* outFile;

public:
	BufferIO(char*, char*);
	~BufferIO(void);

	//Buffer in
	char getNextChar();
	void ungetChar(int);

	int getLine();
	int getColumn();

	bool getEOF();

	//Buffer out
	void out (char*);
	void errorOut(Token);
	void fileOut(char*, unsigned int);
	void writeToFile();
};

