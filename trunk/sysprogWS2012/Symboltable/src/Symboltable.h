/*
 * Symboltable.h
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "List.h"
#include "SymboltableEntry.h"

class Symboltable {
private:
	/**
	* Größe der Hashtable
	*/
	#define SIZE_OF_HASHTABLE 10000

	/**
	 * Hashtabelle, welche SymtabEntries speichert.
	 */
	List<SymboltableEntry*>* hashTable;

	/**
	 *Berechnet einen Hashcode für den angegebenen Schluessel.
	 *
	 *@param key Schlüssel zu welchem der HashCode berechnet werden soll.
	 *@param length Länge des Schlüssels.
	 *@return hashcode
	 */
	int hashCode(char* key, int lenght);



public:

	/**
	 * Initialisiert eine neue Symtable.
	 */
	Symboltable();

	/**
	 * Löscht die Symtable und den Zeiger auf den SymboltableEntry.
	 */
	virtual ~Symboltable();

	/**
	 * Vorbelegung der SymTable, welche die Symtable mit Schlüsselwörtern füllt.
	 */
	void initSymbols();

	/**
	 * Fügt einen neuen Eintrag in die HashTable ein. Dieser enthält den TokenType und
	 * einen Zeiger auf das Lexem, welches zuvor in die SymTable geschrieben wurde.
	 * Nach dem einfügen wird der Zeiger symTabPtr um die eingefügte Anzahl Character
	 * + '\0' hochgezählt.
	 * Es wird nur eingefügt, wenn das Lexem in der HashTable noch nicht vorhanden ist.
	 *
	 * @param lexem welches eingefügt werden soll
	 * @param tokenType welcher zum Lexem gehört
	 * @return HashKey
	 */
	SymboltableEntry* insert(char* lexem, Token::TokenType tokenType);

	/**
		 * Sucht einen eintrag aus der HashTable und gibt einen
		 * Zeiger auf den gewünschten Eintrag zurück.
		 *
		 * @param lexem nach dem gesucht wird.
		 * @return Zeiger auf gefundenes Element. Falls keiner gefunden -> 0
		 */
		SymboltableEntry* lookup(char* lexem);

	//TODO: move to CharHelper
	static int CHARHELPERgetLenght(char*);
	static bool CHARHELPERcompare(char* a, char* b);


};

#endif /* SYMBOLTABLE_H_ */
