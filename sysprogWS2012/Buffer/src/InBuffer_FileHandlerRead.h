#include <fcntl.h> //open
#include <unistd.h> //read
#include <stdio.h>

#include <stdlib.h> //posix_memalign


#ifndef FileHandlerRead_H_
#define FileHandlerRead_H_

class FileHandlerRead {
private:
	char *filePath_;
	int file_;
	int currentFilePos_;
	bool eof_;

	FileHandlerRead();

public:

	FileHandlerRead(char*);
	virtual ~FileHandlerRead();

	void openFile();
	void closeFile();
	char* reading(int);
	bool setFilePos(int);
	bool isEOF();
};

#endif /* FileHandlerRead_H_ */
