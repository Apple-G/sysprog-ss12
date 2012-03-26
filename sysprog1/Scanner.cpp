#include "Scanner.h"
//
//*******************************************************
// Funktion:  Scanner
// Parameter: char* inFile, char* outFile
// Return:    -
// Notiz:     Konstruktor. Es werden die Ein- und Ausgabedatei übergeben.
//*******************************************************
Scanner::Scanner(char* inFile, char* outFile)
{
	//TODO check ob file vorhanden und lesbar eventuell ausgabe, falls outFile überschrieben wird

	buffer = new BufferIO(inFile, outFile);
	automat = new Automat(buffer);
	hashtable = new Hashtable<Token>(10);
}
//========================================================================

//*******************************************************
// Funktion:  ~Scanner
// Parameter: -
// Return:    -
// Notiz:     Destruktor
//*******************************************************
Scanner::~Scanner(void)
{
	delete hashtable;
	//delete automat;
	delete buffer;


}
//========================================================================

//*******************************************************
// Funktion:  initSymbols
// Parameter: char currentChar
// Return:    bool
// Notiz:     Schreibt die Standardzeichen in die Hashtabelle.
//*******************************************************

void Scanner::initSymbols(){
	insert("print", Token("print", Token::print, 0,0,5));
	insert("read", Token("read", Token::read, 0,0,4));
	insert("=", Token("assign\t", Token::sign, 0,0,7));
	insert("+", Token("plus\t", Token::sign, 0,0,5));
	insert("-", Token("minus\t", Token::sign, 0,0,6));
	insert("*", Token("asterisk \t", Token::sign, 0,0,10));
	insert("/", Token("division\t", Token::sign, 0,0,9));
	insert("<", Token("smaller\t", Token::sign, 0,0,8));
	insert(">", Token("larger\t", Token::sign, 0,0,7));
	insert("<=>", Token("<=>\t", Token::sign, 0,0,4));
	insert("!", Token("exclamation mark", Token::sign, 0,0,16));
	insert("&", Token("ampersand\t", Token::sign, 0,0,10));
	insert(";", Token("semicolon\t", Token::sign, 0,0,10));
	insert("(", Token("bracket \t", Token::sign, 0,0,9));
	insert(")", Token("bracket \t", Token::sign, 0,0,9));
	insert("{", Token("bracket \t", Token::sign, 0,0,9));
	insert("}", Token("bracket \t", Token::sign, 0,0,9));
	insert("[", Token("bracket \t", Token::sign, 0,0,9));
	insert("]", Token("bracket \t", Token::sign, 0,0,9));
}
//========================================================================

//*******************************************************
// Funktion:  insert
// Parameter: char* value, Token token
// Return:    void
// Notiz:     Schreibt das übergebene Token in die Haschtabelle.
//*******************************************************
void Scanner::insert(char* value, Token token){
	hashtable->put(value, token);
}
//========================================================================

//*******************************************************
// Funktion:  checkFile
// Parameter: -
// Return:    bool
// Notiz:     Holt sich vom Automat alle Token, wertet sie aus und gibt die Ausgabe an den Puffer weiter.
//*******************************************************
bool Scanner::checkFile(){
	//{ integer=0, identifier=1, sign=2, print=3, read=4, error=-1 };
	initSymbols();
	Token token;
	char* tokenValue;
	while(!buffer->getEOF()){

		token = automat->nextToken();
		tokenValue = copyChar(token.getValue());
		char temp[50];
		switch (token.getType()){
			//error
		case -1:
			buffer->errorOut(token);
			break;
			//integer
		case 0:

			//Ausgabe
			buffer->fileOut("Token Integer\t\tLine: ",21);
			itoa (token.getLine(), temp, 10);
			buffer->fileOut(temp, getCharLength(temp));

			buffer->fileOut(" Column: ",9);
			itoa (token.getColumn(), temp, 10);
			buffer->fileOut(temp, getCharLength(temp));
			buffer->fileOut("\tValue: ",8);
			itoa (token.getIntValue(), temp, 10);
			buffer->fileOut(temp, getCharLength(temp));
			buffer->fileOut("\n",1);
			break;

			//identifier
		case 1:

			if (!hashtable->contains(tokenValue)){
				hashtable->put(tokenValue, token);
			}
			//Ausgabe
			buffer->fileOut("Token Identifier\tLine: ", 23);
			itoa (token.getLine(), temp, 10);
			buffer->fileOut(temp, getCharLength(temp));

			buffer->fileOut(" Column: ",9);
			itoa (token.getColumn(), temp, 10);
			buffer->fileOut(temp, getCharLength(temp));
			buffer->fileOut("\tLexem: ", 8);
			buffer->fileOut(tokenValue, token.getLength());
			buffer->fileOut("\n",1);
			break;

			//Sign
		case 2:
			if (hashtable->contains(tokenValue)){
				//Ausgabe
				buffer->fileOut("Token ",6);
				buffer->fileOut(hashtable->get(tokenValue).getValue(),hashtable->get(tokenValue).getLength());
				buffer->fileOut("\tLine: ",7);
				itoa (token.getLine(), temp, 10);
				buffer->fileOut(temp, getCharLength(temp));
				buffer->fileOut(" Column: ",9);
				itoa (token.getColumn(), temp, 10);
				buffer->fileOut(temp, getCharLength(temp));
				buffer->fileOut("\n",1);
			}
			else{
				std::cout<<"Token unknownSign\tLine: "<<token.getLine()<<" Column: "<<token.getColumn()<<"\tValue: "<<tokenValue<<"##### Error! Zustand nicht möglich #####"<<std::endl;

			}
			break;
		}

	}
	buffer->writeToFile();
	buffer->out("stop");
	return true;
}
//*******************************************************
// Funktion:  main
// Parameter: int argc, char* argv[
// Return:    int
// Notiz:     initialisiert den Scanner, und startet die Analyse.
//*******************************************************
int main(int argc, char* argv[]){
	if (argc < 1) return EXIT_FAILURE;
	Scanner* s = new Scanner(argv[1], argv[2]);
	if (s->checkFile()){
		return EXIT_SUCCESS;
	}
	else{
		return EXIT_FAILURE;
	}

}