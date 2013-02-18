#include "Automat.h"
#include "Token.h"
#include "Buffer.h"
#include "CharHelper.h"
#include "OutBuffer_OutputFileHandler.h"
#include "OutBuffer_OutConsoleHandler.h"
#include "Symboltable.h"
#include <iostream>



int main (int argc, char* argv[])
{
	Symboltable* symboltable = new Symboltable();
	Buffer* b = new Buffer("TestFiles/bible.txt");
	Automat* automat = new Automat(b);

	//Handler

	//File Ausgabe
	OutputHandlerBase* outfile = new OutputFileHandler("TestFiles/out.txt");
	b->RegisterMessageHandler(outfile);

	//Consolen Ausgabe
	OutputHandlerBase* outConsole = new OutConsoleHandler();
	//b->RegisterMessageHandler(outConsole);

	Token t;

	while(!b->isEOF()){
		t=automat->nextToken();
		// std::cout<<(t.getLexem())<<std::endl;
		if (t.getLexem()[0] != '\0')
		{
			b->writeMessage(CharHelper::convertInt(symboltable->insert(t.getLexem(), t.getType())));

			b->writeMessage(" \t Token ");
			b->writeMessage(t.getTypeForOutput());
			int count=0;
			char* tempTokenType = t.getTypeForOutput();
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
