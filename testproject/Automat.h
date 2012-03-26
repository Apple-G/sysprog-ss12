#pragma once
#include "Buffer.h"
#include "Token.h"

class Automat
{
private:
	Buffer* myBuffer;
	char* tempToken;
	int currentState;
	int tempTokenLength;

	static const int STATE_START = 0;
	static const int STATE_IDENTIFIER = 1;
	static const int STATE_INTEGER = 2;
	static const int STATE_SLASH = 3;
	static const int STATE_COMMENTARY = 4;
	static const int STATE_ASTERISK = 5;
	static const int STATE_UNEQUAL = 6;
	static const int STATE_UNEQUAL_CHECK = 7;

	static const int INPUT_LETTER = 0;
	static const int INPUT_NUMBER = 1;
	static const int INPUT_SLASH = 2;
	static const int INPUT_ASTERISK = 3;
	static const int INPUT_UNUSED = 4;
	static const int INPUT_LESSTHAN = 5;
	static const int INPUT_EXCLAMATIONMARK = 6;
	static const int INPUT_GREATERTHAN = 7;
	static const int INPUT_SIGN = 8;
	static const int INPUT_DELIMITER = 9;
	static const int INPUT_ERROR = 10;

	bool isLetter (char);
	bool isDelimiter (char);
	bool isNumber (char);
	bool isSign (char);
	int analyseChar (char);
	void addCharToTempToken(char);
	void stepBack(unsigned int);
	void extendTempToken();
	void shrinkTempToken(unsigned int);
public:
	Token nextToken();
	Automat(Buffer*);
	~Automat(void);
};
