#include "Automat.h"
#include "Token.h"
#include "Buffer.h"
#include "CharHelper.h"
#include "OutBuffer_OutputFileHandler.h"
#include "OutBuffer_OutConsoleHandler.h"
#include <iostream>



int main (int argc, char* argv[])
{
	Automat* automat;

	Buffer *b = new Buffer("TestFiles/newTest.txt");

	//Handler

	//File Ausgabe
	OutputHandlerBase* outfile = new OutputFileHandler("TestFiles/out.txt");
	b->RegisterMessageHandler(outfile);

	//Consolen Ausgabe
	OutputHandlerBase* outConsole = new OutConsoleHandler();
	b->RegisterMessageHandler(outConsole);

	automat = new Automat(b);
	Token t;

	while(!b->isEOF()){
		t=automat->nextToken();
		// std::cout<<(t.getLexem())<<std::endl;

		b->writeMessage("Token ");
		b->writeMessage(t.getType());
		int count=0;
		char* tempTokenType = t.getType();
		while (*tempTokenType != 0)
		{
			count++;
			tempTokenType++;
		}

		if (count<8)
			b->writeMessage("\t");

		b->writeMessage(" \t Line: ");
		b->writeMessage(CharHelper::convertInt(t.getRow()));
		b->writeMessage(" \t Column: ");
		b->writeMessage(CharHelper::convertInt(t.getColumn()));
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
