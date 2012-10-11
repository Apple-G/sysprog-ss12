/*
 * OutConsoleHandler.h
 *
 *  Created on: 27.03.2012
 *      Author: tobias
 */

#ifndef OUTCONSOLEHANDLER_H_
#define OUTCONSOLEHANDLER_H_

#include "OutputHandlerBase.h"

class OutConsoleHandler: public OutputHandlerBase {
public:
	OutConsoleHandler();
	virtual ~OutConsoleHandler();

	void writeBuffer(char*, int);
};

#endif /* OUTCONSOLEHANDLER_H_ */
