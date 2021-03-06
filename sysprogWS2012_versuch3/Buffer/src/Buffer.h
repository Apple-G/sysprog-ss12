#ifndef BUFFER_H_
#define BUFFER_H_
#include "OutputBuffer.h"
#include "InputBuffer.h"

class Buffer {
private:
	OutputBuffer *output_;
	InputBuffer *input_;

public:
	Buffer();
	Buffer(char*, char*, unsigned int);
	virtual ~Buffer();

	char getNextChar();
	void ungetChar(int);

	int getCurrentColumn();
	int getCurrentRow();
	bool isEOF();

	void RegisterMessageHandler(OutputHandlerBase*);
	void RegisterErrorHandler(OutputHandlerBase*);
	void writeMessage(char*);
	void writeMessage(char);
	void writeError(char*);
	void writeToke(void);

	void CloseAll();
};

#endif /* BUFFER_H_ */
