#pragma once
#include "Automat.h"
#include "Buffer.h"
#include "Hashtable.h"
#include "CharOperation.h"

class Scanner
{
private:
	Buffer *buffer;
	Automat *automat;
	Hashtable <Token>*hashtable;

public:
	Scanner(char*, char*);
	~Scanner(void);
	void initSymbols();
	void insert(char*, Token);
	bool checkFile();
};

