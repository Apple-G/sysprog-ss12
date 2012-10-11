/*
 * OutputBuffer.h
 *
 *  Created on: 26.03.2012
 *      Author: tobias
 */

#include "OutputHandlerBase.h"

#ifndef OutputBuffer_H_
#define OutputBuffer_H_

class OutputBuffer {
private:
	static const int  OUT_BUFFER_SIZE = 100;
	static const int MAX_HANDLER = 10;

	char* outBuffer_;
	int outBufferPos_;
	OutputHandlerBase* outMessageHandler_[MAX_HANDLER];
	int outMessageHandlerCounter_;
	OutputHandlerBase* outErrorHandler_[MAX_HANDLER];
	int outErrorHandlerCounter_;

	void writingMessageBuffer();
public:
	OutputBuffer();
	virtual ~OutputBuffer();

	void closeBuffer();

	void writeMessage(char*);
	void writeError(char*);

	void RegisterMessageHandler(OutputHandlerBase*);
	void RegisterErrorHandler(OutputHandlerBase*);
};

#endif /* OutputBuffer_H_ */
