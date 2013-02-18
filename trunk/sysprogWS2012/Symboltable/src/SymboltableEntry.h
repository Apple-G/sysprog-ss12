/**
 * SymboltableEntry stellt einen einzelnen Eintrag in der SymTab dar.
 */

#ifndef __SYMTABENTRY__INCLUDED__
#define __SYMTABENTRY__INCLUDED__

#include "Token.h"

class SymboltableEntry {
	/**
	* Zeiger auf das erste Element des Lexems
	*/
	char* lexem;

	/**
	* Typ des Tokens
	*/
	Token::TokenType tokenType;

public:

	/**
	 * Initialisiert einen neuen Eintrag für die Symtable
	 */
	SymboltableEntry();

	/**
	 * Initialisiert einen neuen Eintrag mit Werten für die Symtable
	 */
	SymboltableEntry(char* lexem, Token::TokenType tokenType);


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
	char* getLexem();



	/**
	 * Setter für TokenType
	 *
	 * @param tokenType Typ des Tokens
	 */
	void setTokenType(Token::TokenType tokenType);

	/**
	 * Getter für den Tokentype
	 *
	 * @return Typ des Tokens
	 */
	Token::TokenType getTokenType() const;

};
#endif // __SYMTABENTRY__INCLUDED__

