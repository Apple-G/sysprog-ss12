/*
 * CharContainer.cpp
 *
 *  Created on: 12.10.2011
 *      Author: tobias
 */

#include "InBuffer_CharContainer.h"

CharContainer::CharContainer(){
}
CharContainer::CharContainer(char symbole, int row, int pos) {
InitializeCharContainer(symbole, row, pos);
}
CharContainer::~CharContainer() {
	// TODO Auto-generated destructor stub
}

void CharContainer::InitializeCharContainer(char symbole, int row, int pos)
{
	symbole_ = symbole;
	row_ = row;
	pos_ = pos;
}

int CharContainer::getPos() const
{
    return pos_;
}

int CharContainer::getRow() const
{
    return row_;
}

char CharContainer::getSymbole() const
{
    return symbole_;
}



