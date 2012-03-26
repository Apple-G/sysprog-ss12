/*
 * FileHandlerWrite.cpp
 *
 *  Created on: 26.03.2012
 *      Author: tobias
 */

#include "FileHandlerWrite.h"

FileHandlerWrite::FileHandlerWrite(char *filePath) {
	filePath_ = filePath;
	outBuffer_ = new char[OUT_BUFFER_SIZE];
	outBufferPos_=0;
	isFileOpen_=false;

}

FileHandlerWrite::~FileHandlerWrite() {
	delete [] filePath_;
	delete [] outBuffer_;
}

void FileHandlerWrite::openFile() {
	file_ = open(filePath_, O_WRONLY);
	if (file_ == -1) {
		isFileOpen_=false;
		// ToDo Fehlerbehandlung
		//throw
	}
	else
	{
		isFileOpen_=true;
	}
}

void FileHandlerWrite::closeFile() {
	wirteBufferToFile();
	outBufferPos_=0;
	close(file_);
	isFileOpen_=false;
}

bool FileHandlerWrite::isFileOpen() {
	return isFileOpen_;
}

void FileHandlerWrite::writeMessage(char* row)
{
	int rowSize = sizeof(row) / sizeof(row[0]);
	for (int i=0; i<rowSize+1; i++)
	{
		//add to Buffer
		if (OUT_BUFFER_SIZE < outBufferPos_+1)
		{
			outBufferPos_++;
			if (i < rowSize)
			{
				outBuffer_[outBufferPos_] = row[i];
			}
			else
			{
				outBuffer_[outBufferPos_] = '\n';
			}

		}
		//Write to File
		else
		{
			wirteBufferToFile();
			outBufferPos_=0;
			i--;
		}
	}

}
void FileHandlerWrite::writeError(char* error)
{
	writingError(error);
	//char* tempBuffer = "Error:" + error;
	//writeBufferToCosole(tempBuffer);
}

void FileHandlerWrite::wirteBufferToFile() {

	if(!isFileOpen())
	{
		openFile();
	}

	int wirteingError = write(file_, outBuffer_, outBufferPos_);
	if (wirteingError <= 0)
		throw "Error";

}
void FileHandlerWrite::writeBufferToCosole(){
	for (int i=0; i<outBufferPos_; i++)
	{
		std::cout<<outBuffer_[i];
	}
}

void FileHandlerWrite::writingError(char* buffer) {
	//ToDo ErrorOutput
	//fprintf(stderr, buffer);
}


