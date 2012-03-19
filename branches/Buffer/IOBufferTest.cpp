#include <iostream>
#include "Buffer.h"

using namespace std;
int main() {
	cout<<"Buffer Test starting..."<<endl;

	Buffer *b = new Buffer("/home/tobias/Dokumente/test.txt", 10);
	char c = b->getNextChar();
	while (c != '\000')
	{
		cout<<"Char:\t"<<c<<" Line: "<<b->getCurrentRow()<<" Column: "<<b->getCurrentRowPosition()<<endl;
		c = b->getNextChar();
	}
delete b;
	cout<<"Buffer Test done"<<endl;
	return 0;
}
