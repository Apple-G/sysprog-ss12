#include "Automat.h"
#include "BufferIO.h"
#include "Hashtable.h"
#include "CharOperation.h"
#include "OwnString.h"
#include "Scanner.h"
#include <conio.h>

void bufferTest(){
//Test Buffer
		BufferIO buffer("test/test.txt", "test/out.txt");
		char *temp = new char[5];
		while (!buffer.getEOF()){
			temp[0] = buffer.getNextChar();
			temp[1] = buffer.getNextChar();
			temp[2] = buffer.getNextChar();
		//	temp[3] ='\0';
			buffer.fileOut(temp, 3);
			//	std::cout<<temp;
		}
		buffer.writeToFile();
		
}

void scannerTest(){
	Scanner scanner("test/test.txt", "test/out.txt");


		scanner.checkFile();
		std::cout<<"stop";
}
/*
int main()
{
	int testcase = 2;

	switch( testcase){
	case 1:
		bufferTest();
		break;
	case 2:
		scannerTest();
		break;
	}
	/*cout<<"Token Identifier\tLine: "<<getCharLength("Token Identifier\tLine: ")<<endl;
	cout<<"\tLexem: "<<getCharLength("\tLexem: ")<<endl;
	cout<<"\tLine:  "<<getCharLength("\tLine: ")<<endl;
	//

	getch();
	return 0;
}*/
