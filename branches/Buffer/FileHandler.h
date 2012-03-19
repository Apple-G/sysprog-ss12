#include <fcntl.h> //open
#include <unistd.h> //read
#include <iostream> //printf
#include <stdio.h>

#include "CharContainer.h"

#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

class FileHandler {
private:
	char *filePath_;
	int file_;
	int currentRow_;
	int currentRowPos_;

public:
	FileHandler();
	FileHandler(char*);
	virtual ~FileHandler();

	void openFile();
	void closeFile();
	char* reading(int);
	CharContainer* fillCharContainer(int);
	void setFilePos(int);
	bool isEOF();

};

#endif /* FILEHANDLER_H_ */
