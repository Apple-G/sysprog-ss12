#include <fcntl.h> //open
#include <unistd.h> //read
#include <iostream> //printf
#include <stdio.h>

#include "InBuffer_CharContainer.h"

#ifndef FileHandlerRead_H_
#define FileHandlerRead_H_

class FileHandlerRead {
private:
	char *filePath_;
	int file_;
	int currentRow_;
	int currentRowPos_;
	bool eof_;

	FileHandlerRead();

public:

	FileHandlerRead(char*);
	virtual ~FileHandlerRead();

	void openFile();
	void closeFile();
	char* reading(int);
	CharContainer* fillCharContainer(int);
	void setFilePos(int);
	bool isEOF();
};

#endif /* FileHandlerRead_H_ */
