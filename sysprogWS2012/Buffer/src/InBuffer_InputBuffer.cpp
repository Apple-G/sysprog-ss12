/*
 * InputBuffer.cpp
 *
 *  Created on: 27.03.2012
 *      Author: tobias
 */
#include "InBuffer_InputBuffer.h"

InputBuffer::InputBuffer(char* filePath, int bufferSize) {
	bufferSize_ = calculateBufferSize(bufferSize);
	bufferNumber_ = 2;
	currentBuffer_ = 0;
	currentBufferPosition_ = -1;

	file_ = new FileHandlerRead(filePath);
	file_->openFile();
	InitializeBuffer();

	currentColumn_ = 0;
	currentRow_ = 1;
	lastLineLengthIndex_ = 50;
	lastLineLength_ = new int[lastLineLengthIndex_];
}

void InputBuffer::InitializeBuffer() {

	if (bufferSize_ < 1) {
		//		throw new InitializationException("Buffer Size has to be bigger 0");
	} else {
		buffer_ = new char*[bufferNumber_];
		for (int i = 0; i < bufferNumber_; i++) {


			fillBuffer(i);
		}
	}
}

unsigned int InputBuffer::changeActiveBuffer() {
	if (currentBuffer_ + 1 < bufferNumber_) {
		return currentBuffer_ + 1;
	}
	return 0;
}

void InputBuffer::fillBuffer(int buferID) {
	buffer_[buferID] = file_->reading(bufferSize_);
}

bool InputBuffer::movePointerForward() {
	currentBufferPosition_++;
	if (currentBufferPosition_ >= bufferSize_) {
		//End of File erreicht
		//	if (file_->isEOF()) {
		//EOF aber nicht ende von Buffer
		if (buffer_[currentBuffer_][currentBufferPosition_ - 1] == '\000') {
			//	currentBuffer_ = changeActiveBuffer();
			//	currentBufferPosition_ = 0;
			//	return true;
			//	}else
			//	{
			return false;
			//	}
		} else {
			//First Fill current Buffer with new Chars
			//then change current Buffer
			fillBuffer(currentBuffer_);
			currentBuffer_ = changeActiveBuffer();
			currentBufferPosition_ = 0;
			return true;
		}
	}
	return true;
}

bool InputBuffer::movePointerBackward() {
	if (currentBufferPosition_ > 0) {
		currentBufferPosition_--;
		return true;
	} else {
		//Fill Buffer
		currentBuffer_ = changeActiveBuffer();

		if (file_->setFilePos(0 - (bufferSize_ * 3))) {
			// bufferSize_ * 3 => es wird immer ein Buffer auf vorraus geladen.
			//Dieser muss mit alten daten überschrieben werden.

			fillBuffer(currentBuffer_);
			//nachdem der Buffer wieder mit allten werten gefüllt wurde muss die Position wieder um die Buffer größe erhöt werden weil dieser Teil bereits im Buffer ist!
			file_->setFilePos(bufferSize_);
			//
			currentBufferPosition_ = bufferSize_ - 1;
			return true;
		}
		return false;
	}
}

InputBuffer::~InputBuffer() {
	// TODO Auto-generated destructor stub
	//delete[] buffer_;
}

char InputBuffer::getNextChar() {
	if (movePointerForward()) {

		char tempChar = buffer_[currentBuffer_][currentBufferPosition_];

		//New Line
		if (tempChar == '\n' || tempChar == '\r') {
			//ToDo '\n' als extra zeichen zählen?
			if (currentRow_ < lastLineLengthIndex_) {
				lastLineLength_[currentRow_] = currentColumn_ + 1;
			}
			//lastRowLengt Array vergrößern
			else {

				int * tempArray = new int[lastLineLengthIndex_ * 2];

				for (int i = 0; i < lastLineLengthIndex_; i++) {
					tempArray[i] = lastLineLength_[i];
				}
				delete[] lastLineLength_;
				lastLineLength_ = tempArray;
				lastLineLengthIndex_ = lastLineLengthIndex_ * 2;
			}
			currentRow_++;

			// 0 => lastLineLength ist relavant
			currentColumn_ = 0;
		} else {
			currentColumn_++;
		}
		return tempChar;
	} else {
		printf("Error: getNextChar.");
		return '\000';
	}
}

char InputBuffer::ungetChar(unsigned int number) {
	char tempChar;
	for (unsigned int i = 0; i < number; i++) {
		tempChar = ungetChar();
	}
	return tempChar;
}

char InputBuffer::ungetChar() {

	if (movePointerBackward()) {
		char tempChar = buffer_[currentBuffer_][currentBufferPosition_];
		//New Line
		if (tempChar == '\n' || tempChar == '\r') {
			//ToDo '\n' als extra zeichen zählen?
			currentRow_--;
			currentColumn_ = lastLineLength_[currentRow_];
			// lastLineLength_ nicht mehr bekannt
		} else {
			currentColumn_--;
		}
		return tempChar;
	} else {
		printf("Error: ungetChar. Linkes Dateiende erreicht!");
		return '\000';
	}
}

int InputBuffer::getCurrentColumn() {
	if (currentColumn_ == 0) {
		return lastLineLength_[currentRow_];
	}
	return currentColumn_;
}

int InputBuffer::getCurrentRow() {
	return currentRow_;
}

void InputBuffer::closeBuffer() {
	file_->closeFile();
}


int InputBuffer::calculateBufferSize(int bufferSize) {
	//vielfaches von PageSize
	 int pagesize = getpagesize();
	 int temp  = bufferSize > pagesize;
	 int returnSize = temp*pagesize;
	 if (bufferSize%pagesize != 0)
	 {
		 returnSize = returnSize+pagesize;
	 }
	 return returnSize;

}

bool InputBuffer::isEOF() {
	return file_->isEOF();
}

