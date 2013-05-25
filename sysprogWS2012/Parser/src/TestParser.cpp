#include <iostream>
#include "Parser.h"
#include "OutBuffer_OutputFileHandler.h"
#include "OutBuffer_OutConsoleHandler.h"
using namespace std;

int main(int argc, char **argv) {


	Buffer* buffer = new Buffer("TestFilesParser/p1Test.txt");

	//File Ausgabe
	OutputHandlerBase* outFile = new OutputFileHandler("out.txt");
	buffer->RegisterMessageHandler(outFile);

//	//Consolen Ausgabe
//	OutputHandlerBase* outConsole = new OutConsoleHandler();
//	buffer->RegisterMessageHandler(outConsole);

	Scanner* scanner = new Scanner(buffer);
	Parser *parser = new Parser(scanner, buffer);
	Tree *tree = parser->parse();

	cout << endl << endl << "Test Parser Complete..." << endl;

}
