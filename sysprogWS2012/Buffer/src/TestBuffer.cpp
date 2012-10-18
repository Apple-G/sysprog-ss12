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

		//delete outfile;
		//delete outConsole;
		cout << "Buffer Test done" << endl;

		//TEST 2
		cout << "Buffer 2Test start..." << endl;
		cout << " a => next Char" << endl;
		cout << " s => ungetChar" << endl;
		cout << " e => exit" << endl;
		Buffer *buffer = new Buffer("TestFiles/test.txt",
						"TestFiles/out.txt", 10);
		//Handler

		buffer->RegisterMessageHandler(outfile);
		buffer->RegisterMessageHandler(outConsole);

		char key;
		while (key != 'e')
		{
			cout<< "Insert: ";
			cin>>key;

			if(key == 'a')
			{
				cout<<"GetNextChar: "<<buffer->getNextChar()<<endl;
			}
			else if (key == 's')
			{
				unsigned int i = 2;
				buffer->ungetChar(i);
				cout<<"UngetNextChar: "<<buffer->getNextChar()<<endl;
			}
		}

		delete b;
		delete buffer;
		return 0;

}
