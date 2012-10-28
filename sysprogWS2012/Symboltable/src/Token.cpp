#include "Token.h"

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
Token::TokenType Token::getType(){
	return this->type;
}
//========================================================================

/*
unsigned int Token::getLength(){
	return length;
}
*/
