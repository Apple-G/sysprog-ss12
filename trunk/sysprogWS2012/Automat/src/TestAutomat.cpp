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
	Buffer* buffer = new Buffer("TestFiles/newTest2.txt");
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

	while(!buffer->isEOF()){
		token = automat->nextToken();

		if (token.getLexem()[0] != '\0')
		{
			if (token.getType() == Token::IDENTIFIER)
			{
				buffer->writeMessage("Token ");
				SymboltableEntry* entry = symboltable->insert(token.getLexem(), token.getType());
				char* tokenType = Token::getTypeForOutput(entry->getTokenType());
				buffer->writeMessage(tokenType);

				buffer->writeMessage(" \t Line: ");
				buffer->writeMessage(CharHelper::convertInt(token.getRow()));
				buffer->writeMessage(" \t Column: ");
				buffer->writeMessage(CharHelper::convertInt(token.getColumn()));
				buffer->writeMessage(" \t Lexem: ");
				buffer->writeMessage(token.getLexem());
				buffer->writeMessage("\n");
			}
			else if (token.getType() == Token::INTEGER)
			{
				buffer->writeMessage("Token ");
				char* tokenType = Token::getTypeForOutput(token.getType());
				buffer->writeMessage(tokenType);

				buffer->writeMessage(" \t Line: ");
				buffer->writeMessage(CharHelper::convertInt(token.getRow()));
				buffer->writeMessage(" \t Column: ");
				buffer->writeMessage(CharHelper::convertInt(token.getColumn()));
				buffer->writeMessage(" \t Value: ");
				buffer->writeMessage(CharHelper::convertLong(token.getNumber()));
				buffer->writeMessage("\n");
			}
			else if (token.getType() == Token::UNKNOWN)
			{
				buffer->writeError("Token ");
				char* tokenType = Token::getTypeForOutput(token.getType());
				buffer->writeError(tokenType);

				buffer->writeError(" \t Line: ");
				buffer->writeError(CharHelper::convertInt(token.getRow()));
				buffer->writeError(" \t Column: ");
				buffer->writeError(CharHelper::convertInt(token.getColumn()));
				buffer->writeError(" \t Symbol: ");
				buffer->writeError(token.getLexem());
				buffer->writeError("\n");
			}
			else
			{
				buffer->writeMessage("Token ");
				char* tokenType = Token::getTypeForOutput(token.getType());
				buffer->writeMessage(tokenType);

				buffer->writeMessage(" \t Line: ");
				buffer->writeMessage(CharHelper::convertInt(token.getRow()));
				buffer->writeMessage(" \t Column: ");
				buffer->writeMessage(CharHelper::convertInt(token.getColumn()));
				buffer->writeMessage("\n");
			}



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
