/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "List.h"
#include "SymboltableEntry.h"


class Symboltable {
public:

	/**
		 * Hashtabelle, welche SymtabEntries speichert.
		 */
		List<SymboltableEntry*>* hashTable;

		/**
		 * StringTable mit fester Länge.
		 */
		char* stringTable;

		/**
		* Pointer welcher Anfangs auf den ersten Index der Stringtable zeigt.
		* Beim einfügen wird der Pointer jeweils auf den letzten Index des eingefügten Lexems gesetzt.
		*/
		char* stringTablePtr;

		/**
		 * Freie Stellen in der StringTable.
		 */
		int stringTableFree;

		/**
		 * Freie Stellen in der HashTable;
		 */
		int hashTableFree;

		/**
		  *Berechnet einen Hashcode für den angegebenen Schluessel.
		  *
		  *@param key Schlüssel zu welchem der HashCode berechnet werden soll.
		  *@param length Länge des Schlüssels.
		  *@return hashcode
		  */
		int hashCode(const char* key, int lenght);

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
		 * Getter für frei Stellen in der SymTable.
		 *
		 * @return freie Stellen
		 */
		int getSymTabFree() const;

		/**
		 * Getter für frei Stellen in der Hashtable.
		 *
		 * @return freie Stellen
		 */
		int getHashTabFree() const;


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
		int insert(const char* lexem, Token::TokenType tokenType);

		/**
		 * Sucht einen eintrag aus der HashTable und gibt einen
		 * Zeiger auf den gewünschten Eintrag zurück.
		 *
		 * @param lexem nach dem gesucht wird.
		 * @return Zeiger auf gefundenes Element. Falls keiner gefunden -> 0
		 */
		SymboltableEntry* lookup(const char* lexem);
};

#endif /* SYMBOLTABLE_H_ */
