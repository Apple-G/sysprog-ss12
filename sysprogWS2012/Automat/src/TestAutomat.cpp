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
	// Measuring Time
	// ======================================================================================================================================
	clock_t begin = clock();

	Symboltable* symboltable = new Symboltable();
	Buffer* buffer = new Buffer("TestFiles/bible.txt");
	Automat* automat = new Automat(buffer);

	//Handler

	//File Ausgabe
	OutputHandlerBase* outfile = new OutputFileHandler("TestFiles/out.txt");
	buffer->RegisterMessageHandler(outfile);

	//Consolen Ausgabe
	OutputHandlerBase* outConsole = new OutConsoleHandler();
	//buffer->RegisterMessageHandler(outConsole);

	Token token;
//TODO: error auf console, rest in datei
//TODO tokentyp aus Symboltabelle lesen
	while(!buffer->isEOF()){
		token = automat->nextToken();
		// std::cout<<(t.getLexem())<<std::endl;
		if (token.getLexem()[0] != '\0')
		{
			buffer->writeMessage(CharHelper::convertInt(symboltable->insert(token.getLexem(), token.getType())));

			buffer->writeMessage("\tToken ");
			buffer->writeMessage(token.getTypeForOutput());
			int count=0;
			char* tempTokenType = token.getTypeForOutput();
			while (*tempTokenType != 0)
			{
				count++;
				tempTokenType++;
			}

			if (count<8)
				buffer->writeMessage("\t");

			buffer->writeMessage(" \t Line: ");
			buffer->writeMessage(CharHelper::convertInt(token.getRow()));
			buffer->writeMessage(" \t Column: ");
			buffer->writeMessage(CharHelper::convertInt(token.getColumn()));
			buffer->writeMessage(" \t Lexem: ");
			buffer->writeMessage(token.getLexem());
			buffer->writeMessage("\n");
		}
	}

	clock_t end = clock();
	// Measuring Time
	// ======================================================================================================================================
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC*1000;
	buffer->writeMessage("\n\nZeitmessung in Millisekunden: ");
	buffer->writeMessage(CharHelper::convertInt(elapsed_secs));

	buffer->CloseAll();
	delete buffer;
	/*Pseudocode
	 *
	 * buffer erstellen (mit textdatei mit lexemen)
	 *
	 * automat muss tokens lesen
	 *
	 *
	 */
}
