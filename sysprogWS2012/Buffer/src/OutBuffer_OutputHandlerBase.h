/*
 * OutputHandlerBase.h
 *
 *  Created on: 27.03.2012
 *      Author: tobias
 */

#ifndef OutputHandlerBase_H_
#define OutputHandlerBase_H_

class OutputHandlerBase {
public:
	OutputHandlerBase();
	virtual ~OutputHandlerBase();

	virtual void writeBuffer(char*, int) = 0;
};

inline OutputHandlerBase::OutputHandlerBase() {
}

inline OutputHandlerBase::~OutputHandlerBase() {
}


#endif /* OutputHandlerBase_H_ */
