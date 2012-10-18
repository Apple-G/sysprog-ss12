#include "Symboltable.h"
#include <iostream>
#include "TokenType.h"

using namespace std;

int main(int argc, char **argv) {

	Symboltable* symboltable;

	symboltable = new Symboltable();


		cout <<"Fuellstand der Symsymboltable: " <<symboltable->getSymTabFree() <<endl;

		        symboltable->insert("*",TokenTypes::ASTERISK);

		        symboltable->insert("+",TokenTypes::PLUS);

		        symboltable->insert("-",TokenTypes::MINUS);

		        symboltable->insert("=",TokenTypes::EQUALS);

		        symboltable->insert("(",TokenTypes::L_PARENTHESIS);

		        symboltable->insert("4",TokenTypes::INTEGER);

		        symboltable->insert(";",TokenTypes::SEMICOLON);

		        symboltable->insert(":",TokenTypes::UNKNOWN);

		        symboltable->insert("-",TokenTypes::MINUS);

		        symboltable->insert("&",TokenTypes::AMPERSAND);

		        symboltable->insert("A",TokenTypes::IDENTIFIER);

		        symboltable->insert("B",TokenTypes::IDENTIFIER);

		        symboltable->insert("+",TokenTypes::PLUS);

		        symboltable->insert("blub",TokenTypes::READ);

		        symboltable->insert("]",TokenTypes::R_SQUAREBRACE);

		        symboltable->insert("7",TokenTypes::INTEGER);

		        symboltable->insert("!",TokenTypes::EXCLAMATIONMARK);

		        cout <<"Fuellstand der Symsymboltable: " <<symboltable->getSymTabFree() <<endl;

		        //Sind schon vorhanden und dürfen nichtmehr gespeichert werden
		        symboltable->insert("+",TokenTypes::PLUS);
		        symboltable->insert("(",TokenTypes::L_PARENTHESIS);
		        symboltable->insert("-",TokenTypes::MINUS);

		        cout <<"Fuellstand der Symsymboltable: " <<symboltable->getSymTabFree() <<endl;


		        cout <<(*symboltable->lookup("+")).getLexem()
		                        <<" ---> " <<(*symboltable->lookup("+")).getTokenType() <<"\n" <<endl;

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
