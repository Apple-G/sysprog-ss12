#include <iostream>
#include "Parser.h"
using namespace std;

int main(int argc, char **argv) {

	Scanner* s = new Scanner("TestFilesParser/p1Test.txt","out.txt");
	Buffer* b = new Buffer();

	Parser *p = new Parser(s, b);
	p->parse();

	cout<<"Test Parser..."<<endl;

}

