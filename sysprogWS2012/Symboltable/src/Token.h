#pragma once
class Token
{
public:
	enum TType { integer=0, identifier=1, sign=2, print=3, read=4, error=-1 };
private:
	char * value;
	long intValue;
	int line;
	int column;
	unsigned int length;
	TType type;

public:
	Token(void);
	Token(char*, TType, int, int, unsigned int);
	Token(long, TType, int, int, unsigned int);
	~Token(void);

	void setValue(char*);
	void setValue(long);
	void setType(TType);
	void setLine(int);
	void setColumn(int);
	void setLength(unsigned int);

	char* getValue();
	long getIntValue();
	int getLine();
	int getColumn();
	unsigned int getLength();
	TType getType();
};

