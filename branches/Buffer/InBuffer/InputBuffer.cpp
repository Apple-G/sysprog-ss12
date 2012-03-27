/*
 * InputBuffer.cpp
 *
 *  Created on: 27.03.2012
 *      Author: tobias
 */
#include "InputBuffer.h"

InputBuffer::InputBuffer(char* filePath, int bufferSize) {
	bufferSize_ = bufferSize;
	bufferNumber_ = 1;
	currentBuffer_ = 0;
	currentBufferPosition_ = -1;

	file_ = new FileHandlerRead(filePath);
	file_->openFile();
	InitializeBuffer();
}

void InputBuffer::InitializeBuffer() {
	if (bufferSize_ < 1) {
			// ToDo Fehlerbehandlung
			printf("Error: Buffer Size is null");
		} else {
			buffer_ = new CharContainer *[bufferNumber_];
			fillBuffer(currentBuffer_);
		}
}

unsigned int InputBuffer::changeActiveBuffer() {
	if (currentBuffer_ + 1 > bufferNumber_) {
		return 0;
	}
	return currentBuffer_ + 1;
}

void InputBuffer::fillBuffer(int aktiveBuffer) {
	//ToDo: Error bei 4 4x buffer füllen?!
		//	delete buffer_[aktiveBuffer];

		//std::cout << "Fill Buffer " << aktiveBuffer << std::endl;
		buffer_[aktiveBuffer] = file_->fillCharContainer(bufferSize_);
}

bool InputBuffer::movePointerForward() {
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

bool InputBuffer::movePointerBackward() {
	//ToDo: movePointerBackward
	return false;
}

InputBuffer::~InputBuffer() {
	// TODO Auto-generated destructor stub
}

char InputBuffer::getNextChar() {
	if (movePointerForward()) {
			return buffer_[currentBuffer_][currentBufferPosition_].getSymbole();
		} else {
			// ToDo Fehlerbehandlung oder nur endoffile
			return '\000';
		}
}

void InputBuffer::ungetChar(int number) {
	for (int i = 0; i < number; i++) {
			if (!movePointerBackward()) {
				// ToDo Fehlerbehandlung
				printf("Error: ungetChar");
			}

		}
}

int InputBuffer::getCurrentColumn() {
	return buffer_[currentBuffer_][currentBufferPosition_].getPos();
}

int InputBuffer::getCurrentRow() {
	return buffer_[currentBuffer_][currentBufferPosition_].getRow();
}

void InputBuffer::closeBuffer() {
	file_->closeFile();
}

bool InputBuffer::isEOF() {
	return file_->isEOF();
}


