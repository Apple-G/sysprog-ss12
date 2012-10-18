/**
 * SymtabEntry stellt einen einzelnen Eintrag in der SymTab dar.
 */

#ifndef __SYMTABENTRY__INCLUDED__
#define __SYMTABENTRY__INCLUDED__

#include "TokenType.h"

class SymtabEntry {
	/**
	* Zeiger auf das erste Element des Lexems
	*/
	char* lexem;

	/**
	* Typ des Tokens
	*/
	TokenTypes::TokenType tokenType;

public:

	/**
	 * Initialisiert einen neuen Eintrag für die Symtable
	 */
	SymtabEntry();

	/**
	 * Initialisiert einen neuen Eintrag mit Werten für die Symtable
	 */
	SymtabEntry(char* lexem, TokenTypes::TokenType tokenType);



	/**
	 * Setter für das Lexem
	 *
	 * @param lexem lexem welches in die Symtable eingefügt werden soll
	 */
	void setLexem(char* lexem);

	/**
	 * Getter für das Lexem
	 *
	 * @return gespeichertes Lexem
	 */
	const char* getLexem();



	/**
	 * Setter für TokenType
	 *
	 * @param tokenType Typ des Tokens
	 */
	void setTokenType(TokenTypes::TokenType tokenType);

	/**
	 * Getter für den Tokentype
	 *
	 * @return Typ des Tokens
	 */
	TokenTypes::TokenType getTokenType() const;

};
#endif // __SYMTABENTRY__INCLUDED__

