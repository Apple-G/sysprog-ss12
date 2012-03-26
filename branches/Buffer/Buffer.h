/*
 * Buffer.h
 *
 *  Created on: 12.10.2011
 *      Author: tobias
 */

#include <iostream> //printf
#include <stdio.h>

#include "CharContainer.h"
#include "FileHandlerRead.h"
#include "FileHandlerWrite.h"

#ifndef BUFFER_H_
#define BUFFER_H_



class Buffer {
private:
	FileHandlerRead *file_;
	FileHandlerWrite *output_;

	unsigned int bufferSize_;
	unsigned int bufferNumber_;
	CharContainer **buffer_;

	unsigned int currentBuffer_;
	unsigned int currentBufferPosition_;

	void InitializeBuffer();
	unsigned int changeActiveBuffer();
	void fillBuffer(int);
	bool movePointerForward();
	bool movePointerBackward();
public:
	Buffer();
	Buffer(char*, char*, unsigned int);
	virtual ~Buffer();

	char getNextChar();
	void ungetChar(int);

	int getCurrentRowPosition();
	int getCurrentRow();

	void writeMessage(char* message);
	void writeError(char* error);
	void writeToke(void);

	bool isEOF();

	void CloseAll();

};

#endif /* BUFFER_H_ */
