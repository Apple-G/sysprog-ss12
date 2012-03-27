#include <iostream>
#include "Buffer.h"
#include "CharHelper.h"

#include "OutBuffer/OutputFileHandler.h"
#include "OutBuffer/OutConsoleHandler.h"

using namespace std;
int main() {
	cout << "Buffer Test starting..." << endl;

	Buffer *b = new Buffer("/home/tobias/Dokumente/test.txt",
			"/home/tobias/Dokumente/out.txt", 10);

	//Handler

	OutputHandlerBase* outfile = new OutputFileHandler(
			"/home/tobias/Dokumente/out.txt");
	b->RegisterMessageHandler(outfile);

	OutputHandlerBase* outConsole = new OutConsoleHandler();
	b->RegisterMessageHandler(outConsole);

	char c;
	c = b->getNextChar();
	while (c != '\000') {
		if (c != '\r' && c != '\n') {
			b->writeMessage("Char: ");
			b->writeMessage(c);
			b->writeMessage("\t\tline: ");
			b->writeMessage(CharHelper::convertInt(b->getCurrentRow()));
			b->writeMessage("\tColumn:");
			b->writeMessage(CharHelper::convertInt(b->getCurrentColumn()));
			b->writeMessage("\r\n");
		}
		c = b->getNextChar();
	}
	b->CloseAll();
	delete b;
	//delete outfile;
	//delete outConsole;
	cout << "Buffer Test done" << endl;
	return 0;
}
