#include "Buffer.h"

Buffer::Buffer() {

}

Buffer::Buffer(char *fileInPath) {
	//TODo: nicht schön, aber funktioniert
	output_ = new OutputBuffer();
	input_ = new InputBuffer(fileInPath, 2);
}

Buffer::Buffer(char *fileInPath, unsigned int bufferSize) {
	output_ = new OutputBuffer();
	input_ = new InputBuffer(fileInPath, bufferSize);
}

Buffer::Buffer(char *fileInPath, char *fileOutPath, unsigned int bufferSize) {
	output_ = new OutputBuffer();
	OutputHandlerBase* outfile = new OutputFileHandler(fileOutPath);
	RegisterMessageHandler(outfile);
	input_ = new InputBuffer(fileInPath, bufferSize);
}

Buffer::~Buffer() {
	delete output_;
	delete input_;
}

char Buffer::ungetChar(unsigned int number) {
	return input_->ungetChar(number);
}

char Buffer::getNextChar() {
	return input_->getNextChar();
}

long Buffer::getCurrentRow() {
	return input_->getCurrentRow();
}

long Buffer::getCurrentColumn() {
	return input_->getCurrentColumn();
}

bool Buffer::isEOF() {
	return input_->isEOF();
}

void Buffer::RegisterMessageHandler(OutputHandlerBase* messageHandler) {
	output_->RegisterMessageHandler(messageHandler);
}

void Buffer::RegisterErrorHandler(OutputHandlerBase* errorHandler) {
	output_->RegisterErrorHandler(errorHandler);
}

void Buffer::CloseAll() {
	input_->closeBuffer();
	output_->closeBuffer();
}

void Buffer::writeMessage(char* message) {
	output_->writeMessage(message);
}

void Buffer::writeMessage(char symbol) {
	output_->writeMessage(&symbol);
}

void Buffer::writeError(char* error) {
	output_->writeError(error);
}

