#include "Automat.h"
#include "Token.h"
#include "Buffer.h"
#include "OutBuffer_OutputFileHandler.h"
#include "OutBuffer_OutConsoleHandler.h"


int main (int argc, char* argv[]){

	Automat* automat;


	Buffer *b = new Buffer("TestFiles/test.txt",
			"TestFiles/out.txt", 10);

	//Handler

	OutputHandlerBase* outfile = new OutputFileHandler(
			"TestFiles/out.txt");
	b->RegisterMessageHandler(outfile);

	OutputHandlerBase* outConsole = new OutConsoleHandler();
	b->RegisterMessageHandler(outConsole);

	automat = new Automat(b);
	Token t;
	while(!b->isEOF()){
		t=automat->nextToken();
		std::cout<<t.getValue() << std::endl;
	}

	/*Pseudocode
	 *
	 * buffer erstellen (mit textdatei mit lexemen)
	 *
	 * automat muss tokens lesen
	 *
	 *
	 */
}
