#include "Automat.h"
#include "Token.h"
#include "Buffer.h"
#include "OutBuffer_OutputFileHandler.h"
#include "OutBuffer_OutConsoleHandler.h"
#include <iostream>



int main (int argc, char* argv[]){

	Automat* automat;


	Buffer *b = new Buffer("TestFiles/newTest.txt",123);

	//Handler

	OutputHandlerBase* outfile = new OutputFileHandler(
			"TestFiles/out.txt");
	b->RegisterMessageHandler(outfile);

	OutputHandlerBase* outConsole = new OutConsoleHandler();
	b->RegisterMessageHandler(outConsole);

	automat = new Automat(b);
	Token t;
	while(!b->isEOF()){
		t=automat->nextToken();
		b->writeMessage(t.getLexem());
		b->writeMessage(" ");
	}

	/*Pseudocode
	 *
	 * buffer erstellen (mit textdatei mit lexemen)
	 *
	 * automat muss tokens lesen
	 *
	 *
	 */
}
