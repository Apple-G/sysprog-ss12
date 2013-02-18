#include "Symboltable.h"
#include <iostream>
#include "Token.h"

using namespace std;

int main(int argc, char **argv) {

	Symboltable* symboltable;

	symboltable = new Symboltable();

	/*char* a = "Test1aasd";
	char* b = "Test1a";
	cout<<"a: "<<symboltable->CHARHELPERgetLenght(a)<<endl;
	cout<<"b: "<<symboltable->CHARHELPERgetLenght(b)<<endl;
	cout<<"a=b: "<<symboltable->CHARHELPERcompare(a,b)<<endl;*/



		        symboltable->insert("read",Token::ASTERISK);



		        symboltable->insert("+",Token::PLUS);
		        cout<<"tests: "<<symboltable->lookup("+")<<endl;

		        symboltable->insert("-",Token::MINUS);

		        symboltable->insert("=",Token::EQUALS);

		        symboltable->insert("(",Token::L_PARENTHESIS);

		        symboltable->insert("4",Token::INTEGER);

		        symboltable->insert(";",Token::SEMICOLON);

		        symboltable->insert(":",Token::UNKNOWN);

		        symboltable->insert("-",Token::MINUS);

		        symboltable->insert("&",Token::AMPERSAND);

		        symboltable->insert("A",Token::IDENTIFIER);

		        symboltable->insert("B",Token::IDENTIFIER);

		        symboltable->insert("+",Token::PLUS);

		        symboltable->insert("blub",Token::READ);

		        symboltable->insert("]",Token::R_SQUAREBRACE);

		        symboltable->insert("7",Token::INTEGER);

		        symboltable->insert("!",Token::EXCLAMATIONMARK);



		        //Sind schon vorhanden und dürfen nichtmehr gespeichert werden
		        symboltable->insert("+",Token::PLUS);
		        symboltable->insert("(",Token::L_PARENTHESIS);
		        symboltable->insert("-",Token::MINUS);





		        cout <<(*symboltable->lookup("read")).getLexem()
		                        <<" ---> " <<(*symboltable->lookup("read")).getTokenType() <<"\n" <<endl;

		        cout <<(*symboltable->lookup("7")).getLexem()
		                        <<" ---> " <<(*symboltable->lookup("7")).getTokenType() <<"\n" <<endl;

		        cout <<(*symboltable->lookup("A")).getLexem()
		                        <<" ---> " <<(*symboltable->lookup("A")).getTokenType() <<"\n" <<endl;

		        cout <<(*symboltable->lookup(":")).getLexem()
		                        <<" ---> " <<(*symboltable->lookup(":")).getTokenType() <<"\n" <<endl;

		        //Name (Lexem) nicht vorhanden
		        if ( symboltable->lookup("wersd451rwq ü34")== 0 )
		        {
		                cout<<"Gibts net!!" <<endl;
		        }


		        return 0;
}
