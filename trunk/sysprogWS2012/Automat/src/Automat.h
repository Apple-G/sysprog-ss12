/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

#include "Buffer.h"
#include "Token.h"
#include <stdlib.h>

class Automat
{
private:
	Buffer* myBuffer;
	char* tempToken;
	int currentState;
	int tempTokenLength;

    const int STATE_START = 0;
    const int STATE_IDENTIFIER = 1;
    const int STATE_INTEGER = 2;
    const int STATE_SLASH = 3;
    const int STATE_COMMENTARY = 4;
    const int STATE_ASTERISK = 5;
    const int STATE_UNEQUAL = 6;
    const int STATE_UNEQUAL_CHECK = 7;

    const int INPUT_LETTER = 0;
    const int INPUT_NUMBER = 1;
    const int INPUT_SLASH = 2;
    const int INPUT_ASTERISK = 3;
    const int INPUT_UNUSED = 4;
    const int INPUT_LESSTHAN = 5;
    const int INPUT_EXCLAMATIONMARK = 6;
    const int INPUT_GREATERTHAN = 7;
    const int INPUT_SIGN = 8;
    const int INPUT_DELIMITER = 9;
    const int INPUT_ERROR = 10;


	bool isLetter (char);
	bool isDelimiter (char);
	bool isNumber (char);
	bool isSign (char);
	int analyseChar (char);
	Token::TokenType analyseSign(char currentChar);
	void addCharToTempToken(char);
	void stepBack(unsigned int);
	void extendTempToken();
	void shrinkTempToken(unsigned int);
public:
	Token nextToken();
	Automat(Buffer*);
	~Automat(void);
};

#endif /* Automat_H_ */