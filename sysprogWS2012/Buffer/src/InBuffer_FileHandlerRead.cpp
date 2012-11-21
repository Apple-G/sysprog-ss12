#include "InBuffer_FileHandlerRead.h"

FileHandlerRead::FileHandlerRead() {
	// TODO Auto-generated constructor stub
}
FileHandlerRead::FileHandlerRead(char *filePath) {
	filePath_ = filePath;
	eof_ = false;
}

FileHandlerRead::~FileHandlerRead() {
	closeFile();
}

void FileHandlerRead::openFile() {
	currentFilePos_ = 0;

	//TODO O_DIRECT
//	file_ = open(filePath_, O_DIRECT);
//	file_ = open(filePath_, O_SYNC|O_DIRECT);
	file_ = open(filePath_, O_RDONLY);
	if (file_ == -1) {
		// ToDo Fehlerbehandlung
		printf("Error: Can't read from File");
		//throw
	}
}

void FileHandlerRead::closeFile() {
	close(file_);
}

char *FileHandlerRead::reading(int charsToRead) {
	char *buffer = new char[charsToRead];

	int numberOfChars = read(file_, buffer, charsToRead);
	if (numberOfChars < 0) {
		// ToDo Fehlerbehandlung
		printf("Error: Reading File Error");
		buffer[numberOfChars] = '\000';
	} else if (numberOfChars == 0 || numberOfChars < charsToRead) {
		buffer[numberOfChars] = '\000';
		eof_ = true;
	}

	currentFilePos_ = currentFilePos_ + charsToRead;


	return buffer;
}

bool FileHandlerRead::setFilePos(int pos) {

	currentFilePos_ = currentFilePos_ + pos;
	if (currentFilePos_ < 0) {
		lseek(file_, 0, SEEK_SET);
		return false;
	}
	lseek(file_, currentFilePos_, SEEK_SET);
	return true;

}
/*
//TODO: DELETE => Funktion wird nicht mehr benötigt
CharContainer* FileHandlerRead::fillCharContainer(int number) {
	CharContainer *container = new CharContainer[number];
	char *buffer = reading(number);

	for (int i = 0; i < number; i++) {
		char c = *(buffer + i);
		container[i].InitializeCharContainer(c, currentRow_, currentRowPos_);
		currentRowPos_++;
		if (c == '\n') {
			currentRow_++;
			currentRowPos_ = 1;
		}

		//EOF
		if (c == '\000') {
			break;
		}
	}
	delete buffer;
	return container;

}*/

bool FileHandlerRead::isEOF() {
	//return SEEK_END == lseek(file_, 0, SEEK_CUR);
	return eof_;
}
