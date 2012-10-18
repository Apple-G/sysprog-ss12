#include <iostream>
#include "TokenType.h"
#include "Symtable.h"

using namespace std;

int main() {

	Symtable table;
	cout <<"Fuellstand der SymTable: " <<table.getSymTabFree() <<endl;

	        table.insert("*",TokenTypes::ASTERISK);

	        table.insert("+",TokenTypes::PLUS);

	        table.insert("-",TokenTypes::MINUS);

	        table.insert("=",TokenTypes::EQUALS);

	        table.insert("(",TokenTypes::L_PARENTHESIS);

	        table.insert("4",TokenTypes::INTEGER);

	        table.insert(";",TokenTypes::SEMICOLON);

	        table.insert(":",TokenTypes::UNKNOWN);

	        table.insert("-",TokenTypes::MINUS);

	        table.insert("&",TokenTypes::AMPERSAND);

	        table.insert("A",TokenTypes::IDENTIFIER);

	        table.insert("B",TokenTypes::IDENTIFIER);

	        table.insert("+",TokenTypes::PLUS);

	        table.insert("blub",TokenTypes::READ);

	        table.insert("]",TokenTypes::R_SQUAREBRACE);

	        table.insert("7",TokenTypes::INTEGER);

	        table.insert("!",TokenTypes::EXCLAMATIONMARK);

	        cout <<"Fuellstand der SymTable: " <<table.getSymTabFree() <<endl;

	        //Sind schon vorhanden und dürfen nichtmehr gespeichert werden
	        table.insert("+",TokenTypes::PLUS);
	        table.insert("(",TokenTypes::L_PARENTHESIS);
	        table.insert("-",TokenTypes::MINUS);

	        cout <<"Fuellstand der SymTable: " <<table.getSymTabFree() <<endl;


	        cout <<(*table.lookup("+")).getLexem()
	                        <<" ---> " <<(*table.lookup("+")).getTokenType() <<"\n" <<endl;

	        cout <<(*table.lookup("7")).getLexem()
	                        <<" ---> " <<(*table.lookup("7")).getTokenType() <<"\n" <<endl;

	        cout <<(*table.lookup("A")).getLexem()
	                        <<" ---> " <<(*table.lookup("A")).getTokenType() <<"\n" <<endl;

	        cout <<(*table.lookup(":")).getLexem()
	                        <<" ---> " <<(*table.lookup(":")).getTokenType() <<"\n" <<endl;

	        //Name (Lexem) nicht vorhanden
	        if ( table.lookup("wersd451rwq ü34")== 0 )
	        {
	                cout<<"Gibts net!!" <<endl;
	        }


	        return 0;

}
