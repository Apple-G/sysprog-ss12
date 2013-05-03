#ifndef NODE_H_
#define NODE_H_

//extern class Visitor;

/* Saemtliche abhaengige Sachen includen */
//ToDo: Visitor
//#include "../TypeCheck/Visitor.h"
/*
#include "NodeProg.h"
#include "NodeDecls.h"
#include "NodeDecl.h"
#include "NodeArray.h"
#include "NodeStatements.h"
#include "NodeStatement.h"
#include "NodeStatementAssign.h"
#include "NodeStatementBlock.h"
#include "NodeStatementIfElse.h"
#include "NodeStatementPrint.h"
#include "NodeStatementRead.h"
#include "NodeStatementWhile.h"

#include "NodeExp.h"
#include "NodeExp2.h"
#include "NodeExp2Exp.h"
#include "NodeExp2IdentifierIndex.h"
#include "NodeExp2Integer.h"
#include "NodeExp2NegativeExp.h"
#include "NodeExp2NotExp.h"

#include "NodeIndex.h"
#include "NodeOpExp.h"
#include "NodeLeaf.h"
#include "NodeOp.h"
#include "NodeIdentifier.h"
#include "NodeInteger.h"
*/
#include <iostream>
#include <typeinfo>

/**
   Allgemeine Beschreibung eines Knotens, um die Anweisungen der Sprache
   systematisch ablegen zu koennen fuer semantische Pruefung und Code-Erzeugung.


*/
class Node {
public:
	/** "Datentypen", die einem Knoten zugeordnet werden können. */
	enum TYPES {
		TYPE_NONE,				/*!< Kein Typ (noch nicht festgelegt */
		TYPE_INTEGER,				/*!< Ganzzahl-Typ (deklaration: int) */
		TYPE_INTEGER_ARRAY,			/*!< Integer-Feld-Typ */
		TYPE_ARRAY,					/*!< Feld-Typ */
		TYPE_ERROR,					/*!< Fehler-Typ (ungültig) */
		TYPE_OP_PLUS,				/*!< '+' Plus */
		TYPE_OP_MINUS,				/*!< '-' Minus */
		TYPE_OP_DIVIDE,				/*!< '/' Division */
		TYPE_OP_MULTIPLY,			/*!< '*' Multiplikation */
		TYPE_OP_GREATER,			/*!< '>' Größer */
		TYPE_OP_SMALLER,			/*!< '<' Kleiner */
		TYPE_OP_EQUAL,				/*!< '=' Gleichheit */
		TYPE_OP_UNEQUAL,			/*!< '<!>' Ungleichheit */
		TYPE_OP_AND					/*!< '&' Logisches Und */
	};

protected:
	/** Zugeordneter Datentyp. */
	Node::TYPES nodeType;

protected:
	Node();

public:
	virtual ~Node(void);

	virtual void accept(Visitor* visitor) = 0;

	virtual void setType(Node::TYPES newType);

	virtual Node::TYPES getType();

	virtual void addChild(Node* node);

	/**
		Ausgabe des Knotens in verstaendlicher Sprache.
	*/
	virtual void dump() = 0;
};

#endif
