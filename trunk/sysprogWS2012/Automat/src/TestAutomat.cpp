#include "Automat.h"
#include "Token.h"
#include "Buffer.h"
#include "OutBuffer_OutputFileHandler.h"
#include "OutBuffer_OutConsoleHandler.h"
#include <iostream>



int main (int argc, char* argv[]){

	Automat* automat;


	Buffer *b = new Buffer("TestFiles/newTest.txt");

	//Handler

	//File Ausgabe
	OutputHandlerBase* outfile = new OutputFileHandler(
			"TestFiles/out.txt");
	b->RegisterMessageHandler(outfile);

	//Consolen Ausgabe
	OutputHandlerBase* outConsole = new OutConsoleHandler();
	b->RegisterMessageHandler(outConsole);

	automat = new Automat(b);
	Token t;
	while(!b->isEOF()){
		t=automat->nextToken();
		b->writeMessage("Token ");
		b->writeMessage(t.getType());
		b->writeMessage(" \t Line: ");
		b->writeMessage(t.getRow());
		b->writeMessage(" \t Column: ");
		b->writeMessage(t.getColumn());
		b->writeMessage(" \t Lexem: ");
		b->writeMessage(t.getLexem());
		b->writeMessage("\n");
	}
	b->CloseAll();
	delete b;
	/*Pseudocode
	 *
	 * buffer erstellen (mit textdatei mit lexemen)
	 *
	 * automat muss tokens lesen
	 *
	 *
	 */
}
