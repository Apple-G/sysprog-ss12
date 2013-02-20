#ifndef TOKEN_H
#define TOKEN_H

class SymboltableEntry;
class Token {
public:
	enum TokenType // getType() Funktion muss synchron zu dieser Tabelle geführt werden
			{
				UNKNOWN,			// ErrorType	0
				INTEGER,			// Integer		1
				IDENTIFIER,			// Bezeichner	2
				PLUS,				// +			3
				MINUS,				// -			4
				SLASH,				// /			5
				ASTERISK,			// *			6
				L_BRACKET,			// <			7
				R_BRACKET,			// >			8
				EQUALS,				// =			9
				EXCLAMATIONMARK,	// !			10
				AMPERSAND,			// &			11
				SEMICOLON,			// ;			12
				L_PARENTHESIS,		// (			13
				R_PARENTHESIS,		// )			14
				L_BRACE,			// {			15
				R_BRACE,			// }			16
				L_SQUAREBRACE,		// [			17
				R_SQUAREBRACE,		// ]			18
				UNEQUAL,			// <!>			19
				PRINT,				// PRINT		20
				READ,				// READ			21
				INT,				// INT			22
				IF,					// if			23
				ELSE,				// else			24
				WHILE,				// while		25
			};

private:
	char* lexem;
	long number;
	int row;
	int column;
//	unsigned int length;
	Token::TokenType type;
	SymboltableEntry* key;
public:
	Token(void);
/*
	//*******************************************************
	// Funktion:  Token
	// Parameter: char* value, TType type, int line, int column
	// Return:    -
	// Notiz:     Konstruktor. �bergeben wird Wert, Typ, Zeile, Spalte.
	//*******************************************************
	Token(char* lexem, TType, int row, int column);

	//*******************************************************
	// Funktion:  Token
	// Parameter: long value, TType type, int line, int column, unsigned int length
	// Return:    -
	// Notiz:     Konstruktor f�r Zahlen. �bergeben wird Wert, Typ, Zeile, Spalte und L�nge.
	//*******************************************************

	Token(long number, TType, int row, int column, unsigned int length);
*/
	~Token(void);

	void setLexem(char*);
	void setNumber(long);
	void setType(TokenType);
	void setRow(int);
	void setColumn(int);
	//void setLength(unsigned int);

	char* getLexem();
	long getNumber();
	int getRow();
	int getColumn();
	//unsigned int getLength();
	char* getTypeForOutput();
	static char* getTypeForOutput(int);
	Token::TokenType getType();

};

#endif /* TOKEN_H */
