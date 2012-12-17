/*
 * InputBuffer.h
 *
 *  Created on: 27.03.2012
 *      Author: tobias
 */

#ifndef InputBuffer_H_
#define InputBuffer_H_

#include "InBuffer_FileHandlerRead.h"

class InputBuffer {
private:
	FileHandlerRead *file_;
	unsigned int bufferSize_;
	unsigned int bufferNumber_;
	char **buffer_;

	unsigned int currentBuffer_;
	unsigned int currentBufferPosition_;

	int currentRow_;
	int *lastLineLength_;
	int lastLineLengthIndex_;
	int currentColumn_;

	int calculateBufferSize(int);

	void InitializeBuffer();
	unsigned int changeActiveBuffer();
	void fillBuffer(int);
	bool movePointerForward();
	bool movePointerBackward();
public:
	InputBuffer(char*, int);
	virtual ~InputBuffer();

	void closeBuffer();

	char getNextChar();
	char ungetChar();
	char ungetChar(unsigned int);

	int getCurrentColumn();
	int getCurrentRow();
	bool isEOF();
};

#endif /* InputBuffer_H_ */
