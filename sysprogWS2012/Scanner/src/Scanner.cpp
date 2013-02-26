#include "Scanner.h"
#include "OutBuffer_OutputFileHandler.h"
#include "OutBuffer_OutConsoleHandler.h"
#include "CharHelper.h"

using namespace std;
//
//*******************************************************
// Funktion:  Scanner
// Parameter: char* inFile, char* outFile
// Return:    -
// Notiz:     Konstruktor. Es werden die Ein- und Ausgabedatei �bergeben.
//*******************************************************
Scanner::Scanner(char* inFile, char* outFile) {
	table = new Symboltable();
	buffer = new Buffer(inFile);
	automat = new Automat(buffer);

	//Handler
	//File Ausgabe
	OutputHandlerBase* outfile = new OutputFileHandler(outFile);
	buffer->RegisterMessageHandler(outfile);

	//Consolen Ausgabe
	OutputHandlerBase* outConsole = new OutConsoleHandler();
	buffer->RegisterMessageHandler(outConsole);
}
//========================================================================

//*******************************************************
// Funktion:  ~Scanner
// Parameter: -
// Return:    -
// Notiz:     Destruktor
//*******************************************************
Scanner::~Scanner(void) {
	delete table;
	delete automat;
	delete buffer;

}

bool Scanner::checkFile() {
	Token token;

	while (!buffer->isEOF()) {
		token = automat->nextToken();

		if (token.getLexem()[0] != '\0') {
			if (token.getType() == Token::IDENTIFIER) {
				buffer->writeMessage("Token ");
				SymboltableEntry* entry = table->insert(token.getLexem(),
						token.getType());
				char* tokenType = Token::getTypeForOutput(
						entry->getTokenType());
				buffer->writeMessage(tokenType);

				buffer->writeMessage(" \t Line: ");
				buffer->writeMessage(CharHelper::convertInt(token.getRow()));
				buffer->writeMessage(" \t Column: ");
				buffer->writeMessage(CharHelper::convertInt(token.getColumn()));
				buffer->writeMessage(" \t Lexem: ");
				buffer->writeMessage(token.getLexem());
				buffer->writeMessage("\n");
			} else if (token.getType() == Token::INTEGER) {
				buffer->writeMessage("Token ");
				char* tokenType = Token::getTypeForOutput(token.getType());
				buffer->writeMessage(tokenType);

				buffer->writeMessage(" \t Line: ");
				buffer->writeMessage(CharHelper::convertInt(token.getRow()));
				buffer->writeMessage(" \t Column: ");
				buffer->writeMessage(CharHelper::convertInt(token.getColumn()));
				buffer->writeMessage(" \t Value: ");
				buffer->writeMessage(
						CharHelper::convertLong(token.getNumber()));
				buffer->writeMessage("\n");
			} else if (token.getType() == Token::UNKNOWN) {
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
			} else {
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
	buffer->CloseAll();
	return true;
}

void Scanner::printToken(Token token) {
	if (token.getLexem()[0] != '\0') {
		if (token.getType() == Token::IDENTIFIER) {
			buffer->writeMessage("Token ");
			char* tokenType = Token::getTypeForOutput(token.getType());
			buffer->writeMessage(tokenType);
			buffer->writeMessage(" \t Line: ");
			buffer->writeMessage(CharHelper::convertInt(token.getRow()));
			buffer->writeMessage(" \t Column: ");
			buffer->writeMessage(CharHelper::convertInt(token.getColumn()));
			buffer->writeMessage(" \t Lexem: ");
			buffer->writeMessage(token.getLexem());
			buffer->writeMessage("\n");
		} else if (token.getType() == Token::INTEGER) {
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
		} else if (token.getType() == Token::UNKNOWN) {
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
		} else {
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

Token* Scanner::getNextToken() {
	Token* token;
	if (!buffer->isEOF()) {
		*token = automat->nextToken();
		if (token->getLexem()[0] != '\0') {
			if (token->getType() == Token::IDENTIFIER) {
				SymboltableEntry* entry = table->insert(token->getLexem(),
						token->getType());
				token->setType(entry->getTokenType());
			}
		}
	}
	//ToDo: DebugAusgabe entfernen
	printToken(*token);

	return token;
}

void Scanner::ungetToken() {
	//ToDo:
}

Scanner::Scanner(Buffer* buffer) {
}

bool Scanner::isEndOfFile() {
	//ToDo:
	return buffer->isEOF();
}

