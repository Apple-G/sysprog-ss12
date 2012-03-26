#include <iostream>
#include "Buffer.h"

using namespace std;
int main() {
	cout<<"Buffer Test starting..."<<endl;

	Buffer *b = new Buffer("/home/tobias/Dokumente/test.txt", "/home/tobias/Dokumente/out.txt", 10);
	char c = b->getNextChar();
	while (c != '\000')
	{
		//b->writeMessage("Char:\t"+c+" Line: "+b->getCurrentColumn()+" Column: "+b->getCurrentRowPosition());
		//b->writeMessage("Test");
		cout<<"Char:\t"<<c<<" Line: "<<b->getCurrentRow()<<" Column: "<<b->getCurrentColumn()<<endl;
		c = b->getNextChar();
	}
delete b;
	cout<<"Buffer Test done"<<endl;
	return 0;
}
