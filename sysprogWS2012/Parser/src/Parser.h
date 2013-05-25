#ifndef Parser_H_
#define Parser_H_

#include "Scanner.h"
#include "Parser_Tree.h"
#include "Token.h"

//include "../Exceptions/InvalidTokenException.h"
//include "../Exceptions/EndOfFileException.h"
//#include "../Exceptions/SyntaxErrorException.h"
//#include "../Exceptions/LookAheadException.h"


/**
	�berpr�ft die Syntax des Programmcodes und erstellt den Strukturbaum.
*/
class Parser
{
	/** 
		Scanner Objekt, benötigt um die Tokens auszulesen und auszuwerten
	*/
	Scanner *scanner;

	Buffer *writer;
	/** 
		Strukturbaum
	*/
	Tree *tree;

	/**
		Kopie des vom Scanner erhaltenen Tokens.
	*/
	Token myToken;
	
	/**
		Weist den Scanner an, dass nächste Token zu lesen
		@return: Pointer (Type: Token)
	*/
	Token *readNextToken();

	/**
		Hilfsfunktion zur Ausgabe von Fehlern
	*/
	void ErrorOutput(char* message, int row, int column);

	/**
		Es folgen die Funktionen für jedes Nicht-Terminalsymbol mit deren Hilfe
		der rekursive Abstieg vollzogen werden kann.
		@return: Pointer (Type: Node)
		@throws: SyntaxErrorException
	*/
	NodeProg* prog();
	NodeDecls* decls();
	NodeDecl* decl();
	NodeArray* array_();
	NodeStatements* statements();
	NodeStatement* statement();
	NodeExp* exp();
	NodeExp2* exp2();
	NodeIndex* index();
	NodeOpExp* op_exp();
	NodeOp* op();
	
	/* Neue Eigenschaften f�r Verschr�nkung */
	/** Wird f�r die semantische Code-Pr�fung eingesetzt. */
	Visitor* typeChecker;

	/** Ist f�r die letztliche Code-Erzeugung zust�ndig. */
	Visitor* codeGenerator;

public:
	/**
		Standardkonstrukor, der den Scanner initialisiert
	*/
	//Parser(char *inFile, char *scannerLog, OutputBuffer *semanticLog, OutputBuffer *outFile);

	Parser(void);
	Parser(Scanner*, Buffer*);
	
	/**
		Erstellt einen Strukturbaum und pr�ft auf die Syntax
		@return: Pointer (Type: Tree)
	*/
	Tree* parse();

	/**
		Destruktor
	*/
	~Parser(void);

	/**
		Getter & Setter
	*/
	Tree* getTree();
};

#endif
