#include "Exception_InputOutputException.h"
#include <iostream>

class StupidErrorException: public InputOutputException {
private:
	char* completeMessage;

public:
	StupidErrorException(char* errorMessage) {
		sprintf(completeMessage, "ERROR: '%s'", errorMessage);
	}

	~StupidErrorException() {
		delete[] completeMessage;
	}

	virtual const char* what() const throw () {
		return this->completeMessage;
	}
};
