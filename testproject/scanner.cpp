/*
 * scanner.cpp
 *
 *  Created on: 26.03.2012
 *      Author: tobias
 */

#include "scanner.h"

#include <iostream>
#include "Buffer.h"

using namespace std;

int main() {
	cout<<"Buffer Test starting..."<<endl;

	Buffer *b = new Buffer("test2.txt", "out.txt", 10);
	char c = b->getNextChar();
	while (c != '\000')
	{
		cout<<"Char:\t"<<c<<" Line: "<<b->getCurrentRow()<<" Column: "<<b->getCurrentColumn()<<endl;
		c = b->getNextChar();
	}
delete b;
	cout<<"Buffer Test done"<<endl;
	return 0;
}
