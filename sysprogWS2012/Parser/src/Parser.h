#pragma once
#include "../Scanner/Scanner.h"
#include "ParseTree\Tree.h"
#include "../Exceptions/InvalidTokenException.h"
#include "../Exceptions/EndOfFileException.h"
#include "../Exceptions/SyntaxErrorException.h"
#include "../Exceptions/LookAheadException.h"


using namespace std;

/**
	Überprüft die Syntax des Programmcodes und erstellt den Strukturbaum.
*/
class Parser
{
	/** 
		Scanner Objekt, benötigt um die Tokens auszulesen und auszuwerten
	*/
	Scanner *scanner;

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
	
	/* Neue Eigenschaften für Verschränkung */
	/** Wird für die semantische Code-Prüfung eingesetzt. */
	Visitor* typeChecker;

	/** Ist für die letztliche Code-Erzeugung zuständig. */
	Visitor* codeGenerator;

public:
	/**
		Standardkonstrukor, der den Scanner initialisiert
	*/
	Parser(char *inFile, char *scannerLog, OutputBuffer *semanticLog, OutputBuffer *outFile);

	Parser(void);
	
	/**
		Erstellt einen Strukturbaum und prüft auf die Syntax
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

