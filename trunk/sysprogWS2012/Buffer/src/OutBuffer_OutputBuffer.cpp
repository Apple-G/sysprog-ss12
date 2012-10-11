/*
 * OutputBuffer.cpp
 *
 *  Created on: 26.03.2012
 *      Author: tobias
 */

#include "OutputBuffer.h"

OutputBuffer::OutputBuffer() {
	outBuffer_ = new char[OUT_BUFFER_SIZE];
	outBufferPos_ = 0;
	outMessageHandlerCounter_= 0;
	outErrorHandlerCounter_ = 0;
}

OutputBuffer::~OutputBuffer() {
	delete[] outBuffer_;
	for (int i=0; i<outErrorHandlerCounter_; i++)
	{
		delete outErrorHandler_[i];
	}
	for (int i=0; i<outMessageHandlerCounter_; i++)
		{
			delete outMessageHandler_[i];
		}
}

void OutputBuffer::closeBuffer() {
	writingMessageBuffer();
}

void OutputBuffer::writeMessage(char* row) {
//todo
	while (*row !=0) {
		if (OUT_BUFFER_SIZE <= outBufferPos_) {

			//Write out Buffer to File
			writingMessageBuffer();
		}

		outBuffer_[outBufferPos_] = *row;
		++outBufferPos_;
		++row;
	}
}

void OutputBuffer::writeError(char* error) {
	//writingError(error);
	//char* tempBuffer = "Error:" + error;
	//writeBufferToCosole(tempBuffer);
}


void OutputBuffer::writingMessageBuffer() {
	for(int i=0; i<outMessageHandlerCounter_; i++)
	{
		outMessageHandler_[i]->writeBuffer(outBuffer_, outBufferPos_);
	}
	outBufferPos_=0;
}

void OutputBuffer::RegisterMessageHandler(OutputHandlerBase* messageHandler) {
	if (outMessageHandlerCounter_ < MAX_HANDLER)
	{
		outMessageHandler_[outMessageHandlerCounter_] = messageHandler;
		outMessageHandlerCounter_++;
	}
}

void OutputBuffer::RegisterErrorHandler(OutputHandlerBase* errorHandler) {
	if (outErrorHandlerCounter_+1 < MAX_HANDLER)
		{
		outErrorHandlerCounter_++;
			outErrorHandler_[outErrorHandlerCounter_] = errorHandler;
		}
}
