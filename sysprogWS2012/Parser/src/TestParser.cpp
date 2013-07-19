#include <iostream>
#include "Parser.h"
#include "OutBuffer_OutputFileHandler.h"
#include "OutBuffer_OutConsoleHandler.h"
using namespace std;

int main(int argc, char **argv) {

	//argv[1] => INPUT-File
	//argv[2] => OUTPUT-File (Code)
	//argv[3] => Error-File //TODo

	if (argc < 2)
	return EXIT_FAILURE;

	Buffer* buffer = new Buffer(argv[1]); /* "TestFilesParser/p1Test.txt" */

		//File Ausgabe
		OutputHandlerBase* outFile = new OutputFileHandler(argv[2]);
		buffer->RegisterMessageHandler(outFile);

	//	//Consolen Ausgabe
	//	OutputHandlerBase* outConsole = new OutConsoleHandler();
	//	buffer->RegisterMessageHandler(outConsole);

		Scanner* scanner = new Scanner(buffer);
		Parser *parser = new Parser(scanner, buffer);
		Tree *tree = parser->parse();
		buffer->CloseAll();

		cout << endl << endl << "Test Parser Complete..." << endl;
		return EXIT_SUCCESS;
}
