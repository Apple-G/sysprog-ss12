#include <iostream>
#include "Buffer.h"
#include "CharHelper.h"

#include "OutBuffer_OutputFileHandler.h"
#include "OutBuffer_OutConsoleHandler.h"

using namespace std;

int main(int argc, char **argv) {

	cout << "Buffer Test starting..." << endl;

		Buffer *b = new Buffer("TestFiles/test.txt",
				"TestFiles/out.txt", 10);

		//Handler

		OutputHandlerBase* outfile = new OutputFileHandler(
				"TestFiles/out.txt");
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
