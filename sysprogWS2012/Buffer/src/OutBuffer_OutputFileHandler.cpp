/*
 * OutputFileHandler.cpp
 *
 *  Created on: 27.03.2012
 *      Author: tobias
 */

#include "OutputFileHandler.h"
#include <fcntl.h> //open
#include <unistd.h> //write
#include <stdio.h>

OutputFileHandler::OutputFileHandler(char* filePath) {
	filePath_ = filePath;
	isFileOpen_ = false;
}

bool OutputFileHandler::isFileOpen() {
	return isFileOpen_;
}

void OutputFileHandler::closeFile() {
	close(file_);
	isFileOpen_ = false;
}

void OutputFileHandler::openFile() {
	file_ = open(filePath_, O_WRONLY | O_CREAT, S_IRWXU);
	if (file_ == -1) {
		isFileOpen_ = false;
		/*	char* errorMessage;
		 sprintf(errorMessage,"Can't Open or Creat File: %s", filePath_);

		 throw new StupidErrorException(errorMessage);*/
		//TODO Exception
		throw "ERROR";
	} else {
		isFileOpen_ = true;
	}
}

OutputFileHandler::~OutputFileHandler() {
}

void OutputFileHandler::writeBuffer(char* buffer, int bufferSize) {
	if (!isFileOpen()) {
		openFile();
	}

	int wirteingError = write(file_, buffer, bufferSize);
	if (wirteingError <= 0) {
		//TODO Exception
		throw "ERROR";
	}

}

