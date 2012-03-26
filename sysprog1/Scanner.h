#pragma once
#include "Automat.h"
#include "BufferIO.h"
#include "Hashtable.h"
#include "CharOperation.h"

class Scanner
{
private:
	BufferIO *buffer;
	Automat *automat;
	Hashtable <Token>*hashtable;

public:
	Scanner(char*, char*);
	~Scanner(void);
	void initSymbols();
	void insert(char*, Token);
	bool checkFile();
};

