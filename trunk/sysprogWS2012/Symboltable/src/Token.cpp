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
char* Token::getType(){
	switch (this->type)
	{
	case INTEGER: 			return "INTEGER";
	case IDENTIFIER: 		return "IDENTIFIER";
	case PLUS: 				return "+";
	case MINUS: 			return "-";
	case SLASH: 			return "/";
	case ASTERISK: 			return "*";
	case L_BRACKET: 		return "<";
	case R_BRACKET: 		return ">";
	case EQUALS: 			return "=";
	case EXCLAMATIONMARK: 	return "!";
	case AMPERSAND: 		return "&";
	case SEMICOLON: 		return ";";
	case L_PARENTHESIS: 	return "(";
	case R_PARENTHESIS: 	return ")";
	case L_BRACE: 			return "{";
	case R_BRACE: 			return "}";
	case L_SQUAREBRACE: 	return "[";
	case R_SQUAREBRACE: 	return "]";
	case UNEQUAL: 			return "<!>";
	case PRINT: 			return "print";
	case READ: 				return "read";
	default: 				return "UNKNOWN";
	}
}
//========================================================================

/*
unsigned int Token::getLength(){
	return length;
}
*/
