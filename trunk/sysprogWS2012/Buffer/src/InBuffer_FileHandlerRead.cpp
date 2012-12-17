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
	file_ = open(filePath_, O_RDONLY | O_DIRECT);
	if (file_ == -1) {
		this->eof_ = true;
		printf("Error: Can't read from File");
	}
}

void FileHandlerRead::closeFile() {
	close(file_);
}

char *FileHandlerRead::reading(int charsToRead) {

	char *buffer = new char[charsToRead];

	//Bufferspeicher initialisieren
	posix_memalign((void **) &buffer, charsToRead, charsToRead);

	int numberOfChars = read(file_, buffer, charsToRead);
	if (numberOfChars < 0) {
		this->eof_ = true;
		printf("Error: Reading File Error");
		return '\000';
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

bool FileHandlerRead::isEOF() {
	//return SEEK_END == lseek(file_, 0, SEEK_CUR);
	return eof_;
}
