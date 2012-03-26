/*
 * FileHandlerWrite.h
 *
 *  Created on: 26.03.2012
 *      Author: tobias
 */

#include <fcntl.h> //open
#include <unistd.h> //write
#include <iostream> //printf

#ifndef FileHandlerWrite_H_
#define FileHandlerWrite_H_

class FileHandlerWrite {
private:
	static const int  OUT_BUFFER_SIZE = 100;
	char *filePath_;
	int file_;
	char* outBuffer_;
	int outBufferPos_;
	bool isFileOpen_;
	void wirteBufferToFile();
	void writeBufferToCosole();
	void writingError(char*);

public:
	FileHandlerWrite(char*);
	virtual ~FileHandlerWrite();

	bool isFileOpen();
	void closeFile();
	void openFile();

	void writeMessage(char*);
	void writeError(char*);
};

#endif /* FileHandlerWrite_H_ */
