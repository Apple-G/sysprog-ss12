#include "Token.h"
#include "SymboltableEntry.h"
//*******************************************************
// Funktion:  Token
// Parameter: -
// Return:    -
// Notiz:     Konstruktor
//*******************************************************
Token::Token()
{
	this->lexem = "";
	this->number = 0;
	this->type = UNKNOWN;
	this->row = 0;
	this->column = 0;
}
/*TODO werden im moment nicht benötigt
Token::Token(char* value, TType type, int line, int column,unsigned int length)
{
	this->value = value;
	this->intValue = 0;
	this->type = type;
	this->line = line;
	this->column = column;
	this->length = length;
}
Token::Token(long value, TType type, int line, int column, unsigned int length)
{
	this->intValue = value;
	this->value = "";
	this->type = type;
	this->line = line;
	this->column = column;
	this->length = length;
}

*/
//========================================================================


//*******************************************************
// Funktion:  ~Token
// Parameter: -
// Return:    -
// Notiz:     Destruktor
//*******************************************************
Token::~Token(void)
{
	//delete value;
}
//========================================================================

void Token::setLexem(char* lexem){
	this->lexem = lexem;
}
//========================================================================

/**
* 
**/
void Token::setNumber(long number){
	this->number = number;
}
//========================================================================

void Token::setType(TokenType type){
	this->type = type;
}
//========================================================================

/**
* 
**/
void Token::setRow(int row){
	this->row = row;
}
//========================================================================

void Token::setColumn(int column){
	this->column = column;
}
//========================================================================

/**
* 
**
void Token::setLength(unsigned int length){
	this->length = length;
}*/
//========================================================================

char* Token::getLexem(){
	return this->lexem;
}
//========================================================================

long Token::getNumber(){
	return this->number;
}
//========================================================================

/**
* 
**/
int Token::getRow(){
	return this->row;
}
//========================================================================

int Token::getColumn(){
	return this->column;
}
//========================================================================

/**
* 
**/
char* Token::getTypeForOutput(int type)
{
	// enum TokenType muss synchron zu diesen Ausgaben geführt werden, sonst wird UNKNOWN geliefert
	switch (type)
	{
	case INTEGER: 			return "Integer       ";
	case IDENTIFIER: 		return "Identifier    ";
	case PLUS: 				return "Plus          ";
	case MINUS: 			return "Minus         ";
	case SLASH: 			return "Divide        ";
	case ASTERISK: 			return "Multiply      ";
	case L_BRACKET: 		return "Smaller than  ";
	case R_BRACKET: 		return "Bigger than   ";
	case EQUALS: 			return "Assign        ";
	case EXCLAMATIONMARK: 	return "Exc.mark      ";
	case AMPERSAND: 		return "Ampersand     ";
	case SEMICOLON: 		return "Semicolon     ";
	case L_PARENTHESIS: 	return "L. Parenthesis";
	case R_PARENTHESIS: 	return "R. Parenthesis";
	case L_BRACE: 			return "L Brace       ";
	case R_BRACE: 			return "R Brace       ";
	case L_SQUAREBRACE: 	return "L Squarebrace ";
	case R_SQUAREBRACE: 	return "R Squarebrace ";
	case UNEQUAL: 			return "Unequal       ";
	case PRINT: 			return "print         ";
	case READ: 				return "read          ";
	case INT: 				return "int           ";
	case IF: 				return "if            ";
	case ELSE: 				return "else          ";
	case WHILE: 			return "while         ";
	default: 				return "Unknown       ";
	}
}

char* Token::getTypeForOutput()
{
	return Token::getTypeForOutput(this->type);
}
//========================================================================

Token::TokenType Token::getType()
{
	return this->type;
}

/*
unsigned int Token::getLength(){
	return length;
}
*/
