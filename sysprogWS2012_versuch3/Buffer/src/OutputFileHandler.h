/*
 * OutputFileHandler.h
 *
 *  Created on: 27.03.2012
 *      Author: tobias
 */

#ifndef OUTPUTFILEHANDLER_H_
#define OUTPUTFILEHANDLER_H_

#include "OutputHandlerBase.h"

class OutputFileHandler: public OutputHandlerBase {
private:
	char *filePath_;
	int file_;
	bool isFileOpen_;

	bool isFileOpen();
	void closeFile();
	void openFile();
public:
	OutputFileHandler(char*);
	virtual ~OutputFileHandler();
	void writeBuffer(char*, int);
};

#endif /* OUTPUTFILEHANDLER_H_ */
