/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

#include "Token.h"

class Automat
{
private:
	BufferIO* myBuffer;
	char* tempToken;
	int currentState;
	int tempTokenLength;

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
	Automat(BufferIO*);
	~Automat(void);
};

#endif /* Automat_H_ */
