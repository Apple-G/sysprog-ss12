/*
 * Buffer.cpp
 *
 *  Created on: 12.10.2011
 *      Author: tobias
 */

#include "Buffer.h"

Buffer::Buffer() {

}

Buffer::Buffer(char *filePath, unsigned int bufferSize) {
	bufferSize_ = bufferSize;
	bufferNumber_ = 1;
	currentBuffer_ = 0;
	currentBufferPosition_ = -1;
	try {
		file_ = new FileHandler(filePath);
		file_->openFile();
		InitializeBuffer();
	} catch (int i) //Error Buffersize
	{
	} catch (...) //Error File
	{
	}
}

Buffer::~Buffer() {
	delete buffer_; //todo:
	delete file_;
}

void Buffer::InitializeBuffer() {
	if (bufferSize_ < 1) {
		// ToDo Fehlerbehandlung
		printf("Error: Buffer Size is null");
	} else {
		buffer_ = new CharContainer *[bufferNumber_];
		fillBuffer(currentBuffer_);
	}
}

void Buffer::fillBuffer(int aktiveBuffer) {
	//ToDo: Error bei 4 4x buffer füllen?!
	//	delete buffer_[aktiveBuffer];

	//std::cout << "Fill Buffer " << aktiveBuffer << std::endl;
	buffer_[aktiveBuffer] = file_->fillCharContainer(bufferSize_);
}

unsigned int Buffer::changeActiveBuffer() {
	if (currentBuffer_ + 1 > bufferNumber_) {
		return 0;
	}
	return currentBuffer_ + 1;

}

bool Buffer::movePointerBackward() {
	//ToDo: movePointerBackward
	return false;
}

bool Buffer::movePointerForward() {
	currentBufferPosition_++;
	if (currentBufferPosition_ >= bufferSize_) {
		if (file_->isEOF()) {
			return false;
		} else {
			currentBuffer_ = changeActiveBuffer();
			fillBuffer(currentBuffer_);
			currentBufferPosition_ = 0;
			return true;
		}
	}
	return true;
}

void Buffer::ungetChar(int number) {
	for (int i = 0; i < number; i++) {
		if (!movePointerBackward()) {
			// ToDo Fehlerbehandlung
			printf("Error: ungetChar");
		}

	}
}

char Buffer::getNextChar() {

	if (movePointerForward()) {
		return buffer_[currentBuffer_][currentBufferPosition_].getSymbole();
	} else {
		// ToDo Fehlerbehandlung oder nur endoffile
		return '\000';
	}
}

int Buffer::getCurrentRow() {
	return buffer_[currentBuffer_][currentBufferPosition_].getRow();
}

int Buffer::getCurrentRowPosition() {
	return buffer_[currentBuffer_][currentBufferPosition_].getPos();
}


