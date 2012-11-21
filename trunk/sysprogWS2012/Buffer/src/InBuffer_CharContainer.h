/*
 * CharContainer.h
 *
 *  Created on: 12.10.2011
 *      Author: tobias
 */
/*
#include <iostream> //printf
#include <stdio.h>

#ifndef CHARCONTAINER_H_
#define CHARCONTAINER_H_

class CharContainer {
private:
	char symbole_;
	int row_;
	int pos_;
public:
	CharContainer();
	CharContainer(char, int, int);

	virtual ~CharContainer();

	void InitializeCharContainer(char, int, int);
    int getPos() const;
    int getRow() const;
    char getSymbole() const;
};

#endif /* CHARCONTAINER_H_ */

