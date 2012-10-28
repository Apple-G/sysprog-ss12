/**
 * SymboltableEntry stellt einen einzelnen Eintrag in der SymTab dar.
 */
#include "SymboltableEntry.h"

/**
 * Initialisiert einen neuen Eintrag für die SymTab.
 */
SymboltableEntry::SymboltableEntry()
{
	this->lexem = 0;
	this->tokenType = Token::UNKNOWN;
}

/**
 * Initialisiert einen neuen Eintrag für die SymTab mit den übergebenen Werten.
 */
SymboltableEntry::SymboltableEntry(char* lexem, Token::TokenType tokenType)
{
	this->lexem = lexem;
	this->tokenType = tokenType;
}

/**
 * Setter für das Lexem
 *
 * @param lexem lexem welches in die Symtable eingefügt werden soll.
 */
void SymboltableEntry::setLexem(char* lexem)
{
	this->lexem = lexem;
}

/**
 * Getter für das Lexem
 *
 * @return gespeichertes Lexem
 */
const char* SymboltableEntry::getLexem()
{
	return this->lexem;
}

/**
 * Setter für TokenType
 *
 * @param tokenType Typ des Tokens
 */
void SymboltableEntry::setTokenType(Token::TokenType tokenType)
{
	this->tokenType = tokenType;
}

/**
 * Getter für TokenType
 *
 * @return Typ des Tokens
 */
Token::TokenType SymboltableEntry::getTokenType() const
{
	return this->tokenType;
}
