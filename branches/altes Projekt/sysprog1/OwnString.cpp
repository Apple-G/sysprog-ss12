#include "OwnString.h"

/**
* standard constructor
**/
OwnString::OwnString(void)
{
	word = "";
}

/**
* constructor
**/
OwnString::OwnString(char* word)
{
	this->length = getWordLength(word);
	this->word = new char[length];
	for (int i = 0; i<this->length; i++){
		this->word[i] = word[i];
	}
	this->word[this->length]='\0';

}

/**
* 
**/
OwnString::~OwnString(void)
{
	delete word;
}

/**
* 
**/
void OwnString::extendChar(int length){

	char* temp;

	temp = new char[this->length];
	for (int i=0; i<this->length; i++){
		temp[i] = word[i];
	}
	//delete[] this->word;

	this->word = new char[length];
	for (int i=0; i<length; i++){
		word[i] = temp[i];
	}
	word[length] ='\0';
	this->length += length;

	delete[] temp;

}

/**
* 
**/
int OwnString::getWordLength(char* word){
	int i = 0;
	while (word[i] != '\0'){
		i++;
	}
	return i;
}

/**
* 
**/
int OwnString::getLength(){
	return length;
}

/**
* 
**/
char* OwnString::getWord(){
	return this->word;
}

/**
* 
**/
void OwnString::operator=(OwnString& op1){
	//delete word;
	this->length = op1.getLength();
	word = new char[length];
	for (int i = 0; i<this->length; i++){
		this->word[i] = op1.getWord()[i];
	}
	this->word[this->length+1]='\0';
}

void OwnString::operator=(char* word){
	//delete word;
	this->length = this->getWordLength(word);
	this->word = new char[length];
	for (int i = 0; i<this->length; i++){
		this->word[i] = word[i];
	}
	this->word[this->length]='\0';
}
/**
* 
**/
void OwnString::operator+(char* word){
	int oldLength = this->length;
	extendChar(getWordLength(word));

	for (int i=0; i<getWordLength(word); i++){
		this->word[i+oldLength] = word[i];
	}
	this->word[this->length] ='\0';
}

/**
* 
**//*
OwnString operator+(OwnString& op1, OwnString& op2){
	int length = op1.getLength() + op2.getLength();
	char* word = new char[length+1];

	for (int i=0; i<op1.getLength(); i++){
		word[i] = op1.getWord()[i];
	}
	for (int i=0; i<op2.getLength(); i++){
		word[i+op1.getLength()] = op2.getWord()[i];
	}
	word[length]='\0';

	OwnString temp(word);
	return temp;
}*/