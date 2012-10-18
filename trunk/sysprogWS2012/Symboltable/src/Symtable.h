#include "TokenType.h"
#include "List.h"
#include "SymtabEntry.h"

#ifndef SYMTABLE_H_
#define SYMTABLE_H_



class Symtable {

	/**
	 * Hashtabelle, welche SymtabEntries speichert.
	 */
	List<SymtabEntry*>* hashTable;

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
	Symtable();


	/**
	 * Löscht die Symtable und den Zeiger auf den SymtabEntry.
	 */
	~Symtable();

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
	int insert(const char* lexem, TokenTypes::TokenType tokenType);

	/**
	 * Sucht einen eintrag aus der HashTable und gibt einen
	 * Zeiger auf den gewünschten Eintrag zurück.
	 *
	 * @param lexem nach dem gesucht wird.
	 * @return Zeiger auf gefundenes Element. Falls keiner gefunden -> 0
	 */
	SymtabEntry* lookup(const char* lexem);

};

#endif // SYMTABLE_H_

