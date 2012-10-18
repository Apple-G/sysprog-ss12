/**
 * SymtabEntry stellt einen einzelnen Eintrag in der SymTab dar.
 */

#include "SymtabEntry.h"

/**
 * Initialisiert einen neuen Eintrag für die SymTab.
 */
SymtabEntry::SymtabEntry()
{
	this->lexem = 0;
	this->tokenType = TokenTypes::UNKNOWN;
}

/**
 * Initialisiert einen neuen Eintrag für die SymTab mit den übergebenen Werten.
 */
SymtabEntry::SymtabEntry(char* lexem, TokenTypes::TokenType tokenType)
{
	this->lexem = lexem;
	this->tokenType = tokenType;
}

/**
 * Setter für das Lexem
 *
 * @param lexem lexem welches in die Symtable eingefügt werden soll.
 */
void SymtabEntry::setLexem(char* lexem)
{
	this->lexem = lexem;
}

/**
 * Getter für das Lexem
 *
 * @return gespeichertes Lexem
 */
const char* SymtabEntry::getLexem()
{
	return this->lexem;
}

/**
 * Setter für TokenType
 *
 * @param tokenType Typ des Tokens
 */
void SymtabEntry::setTokenType(TokenTypes::TokenType tokenType)
{
	this->tokenType = tokenType;
}

/**
 * Getter für TokenType
 *
 * @return Typ des Tokens
 */
TokenTypes::TokenType SymtabEntry::getTokenType() const
{
	return this->tokenType;
}
