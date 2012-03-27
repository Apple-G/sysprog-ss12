#include "FileHandlerRead.h"

FileHandlerRead::FileHandlerRead() {
	// TODO Auto-generated constructor stub
}
FileHandlerRead::FileHandlerRead(char *filePath) {
	filePath_ = filePath;
}

FileHandlerRead::~FileHandlerRead() {
	closeFile();
}

void FileHandlerRead::openFile() {
	currentRow_ = 1;
	currentRowPos_ = 1;
//	file_ = open(filePath_, O_DIRECT);
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

char *FileHandlerRead::reading(int number) {
	char *buffer = new char[number];
	int error = read(file_, buffer, number);
	if (error < 0) {
		// ToDo Fehlerbehandlung
		printf("Error: Reading File Error");
	} else if (error == 0 || error < number) {
		//ToDo: error < number; error = die anzahl der gelesenen Zeichen! vll überarbeiten
		buffer[error] = '\000';
		//ToDo End of File
	//	printf("End of File!");
	}
	return buffer;
}

void FileHandlerRead::setFilePos(int pos) {
	lseek(file_, pos, SEEK_CUR);
}

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
		//	printf("End of File!");
			break;
		}
	}
	delete buffer;
	return container;

}

bool FileHandlerRead::isEOF() {
	return SEEK_END == lseek(file_, 0, SEEK_CUR);
}
