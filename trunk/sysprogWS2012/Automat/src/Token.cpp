#include "Token.h"

//*******************************************************
// Funktion:  Token
// Parameter: -
// Return:    -
// Notiz:     Konstruktor
//*******************************************************
Token::Token()
{
	this->value = "";
	this->intValue = 0;
	this->type = error;
	this->line = 0;
	this->column = 0;
}
//*******************************************************
// Funktion:  Token
// Parameter: char* value, TType type, int line, int column,unsigned int length
// Return:    -
// Notiz:     Konstruktor. Übergeben wird Wert, Typ, Zeile, Spalte und Länge.
//*******************************************************
Token::Token(char* value, TType type, int line, int column,unsigned int length)
{
	this->value = value;
	this->intValue = 0;
	this->type = type;
	this->line = line;
	this->column = column;
	this->length = length;
}


//*******************************************************
// Funktion:  Token
// Parameter: long value, TType type, int line, int column, unsigned int length
// Return:    -
// Notiz:     Konstruktor für Zahlen. Übergeben wird Wert, Typ, Zeile, Spalte und Länge. 
//*******************************************************

Token::Token(long value, TType type, int line, int column, unsigned int length)
{
	this->intValue = value;
	this->value = "";
	this->type = type;
	this->line = line;
	this->column = column;
	this->length = length;
}
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

void Token::setValue(char* value){
	this->value = value;
}
//========================================================================

/**
* 
**/
void Token::setValue(long value){
	this->intValue = value;
}
//========================================================================

void Token::setType(TType type){
	this->type = type;
}
//========================================================================

/**
* 
**/
void Token::setLine(int line){
	this->line = line;
}
//========================================================================

void Token::setColumn(int column){
	this->column = column;
}
//========================================================================

/**
* 
**/
void Token::setLength(unsigned int length){
	this->length = length;
}
//========================================================================

char* Token::getValue(){
	return value;
}
//========================================================================

long Token::getIntValue(){
	return intValue;
}
//========================================================================

/**
* 
**/
int Token::getLine(){
	return line;
}
//========================================================================

int Token::getColumn(){
	return column;
}
//========================================================================

/**
* 
**/
Token::TType Token::getType(){
	return type;
}
//========================================================================

unsigned int Token::getLength(){
	return length;
}
