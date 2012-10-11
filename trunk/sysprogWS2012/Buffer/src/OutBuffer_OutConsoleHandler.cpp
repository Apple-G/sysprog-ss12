/*
 * OutConsoleHandler.cpp
 *
 *  Created on: 27.03.2012
 *      Author: tobias
 */

#include "OutConsoleHandler.h"
#include <iostream>

OutConsoleHandler::OutConsoleHandler() {
	// TODO Auto-generated constructor stub
}

OutConsoleHandler::~OutConsoleHandler() {
	// TODO Auto-generated destructor stub
}

void OutConsoleHandler::writeBuffer(char* buffer, int bufferSize) {
	for (int i = 0; i < bufferSize; i++) {
		std::cout << buffer[i];
	}
}

