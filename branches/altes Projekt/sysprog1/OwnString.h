#pragma once
class OwnString
{
private:
	char * word;
	int length; 
	
public:
	OwnString();
	OwnString(char *word);
	~OwnString(void);
	//OwnString& operator+=( const OwnString& op2);
	void operator=(OwnString& op1);
	void operator=(char* word);
	void operator+(char* word);
	int getLength(); 
	int getWordLength(char * word);
	char* getWord();
	void extendChar(int length);
};
//extern OwnString operator+(OwnString& op1, OwnString& op2);