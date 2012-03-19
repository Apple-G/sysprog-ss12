/*
 * Buffer.h
 *
 *  Created on: 12.10.2011
 *      Author: tobias
 */

#include <iostream> //printf
#include <stdio.h>

#include "CharContainer.h"
#include "FileHandler.h"

#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer {
private:
	FileHandler *file_;

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
	Buffer(char*, unsigned int);
	virtual ~Buffer();

	char getNextChar();
	void ungetChar(int);

	int getCurrentRowPosition();
	int getCurrentRow();

};

#endif /* BUFFER_H_ */
