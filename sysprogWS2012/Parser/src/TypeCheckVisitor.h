#ifndef TypeCheckVisitor_H_
#define TypeCheckVisitor_H_
#include "Visitor.h"
#include "Buffer.h"

/**
   Dieser Visitor durchl�uft eine baumartige Struktur von Programmanweisungen, welche
   vom Parser erzeugt wurde. Entsprechend der Regeln der Sprache und der Strukturen
   wird eine semantische (Typ-) Pruefung durchgefuehrt und Fehler gemeldet.

*/
class TypeCheckVisitor : public Visitor {
	/** Maximale Fehlermeldungs-Laenge. */
	static const unsigned int ERROR_MESSAGE_SIZE = 2048;

	/** Benutztes Ausgabeinterface, um Code wegzuschreiben. */
	Buffer *writer;

	/** C-String der aktuellen Fehlermeldung - Puffer zum Wegschreiben. */
	char errorMessage[ERROR_MESSAGE_SIZE];

	/** Fehlerzaehler um am Ende ermitteln zu koennen, ob welche aufgetreten sind. */
	unsigned int errorCount;

	/** Erzeugt eine Fehlermeldung und schreibt diese weg.
	@param message String nach printf Muster.
	@param line Zeile, in der der Fehler gefunden wurde.
	@param column Spalte, in der der Fehler gefunden wurde.
	@param lexem Lexem, das mit dem Fehler zu tun hat.
	@param lexemLength Laenge des Lexems - vereinfacht Kuerzung.
	*/
	virtual void outputError(char *message, unsigned int line, unsigned int column, char *lexem = NULL);

	/** Schreibt die aktuelle Fehlermeldung weg. */
//	virtual void flushError(void);

public:
	/** Erzeugt einen neuen Visitor und initialisiert internen Zustand.
	    Ausgaben finden dann ueber stderr statt.
	*/
	//ToDo: TypeCheckVisitor::TypeCheckVisitor();
	TypeCheckVisitor();

	/** Erzeugt einen neuen Visitor und initialisiert internen Zustand.
	@param writer Hierueber werden die Ausgaben weggeschrieben, oder ueber stderr wenn 0.
	*/
	TypeCheckVisitor(Buffer *writer);

	/** Gibt auf Heap verwendeten Speicher wieder frei. */
	virtual ~TypeCheckVisitor(void);

	/* Geht jeweilige Node durch und fuehrt Typpruefung entsprechend der Spezifikationen durch. */
	virtual void visit(NodeProg *node);
	
	virtual void visit(NodeDecls *node);
	virtual void visit(NodeDecl *node);

	virtual void visit(NodeArray *node);

	virtual void visit(NodeStatements *node);
	virtual void visit(NodeStatementAssign *node);
	virtual void visit(NodeStatementBlock *node);
	virtual void visit(NodeStatementIfElse *node);
	virtual void visit(NodeStatementPrint *node);
	virtual void visit(NodeStatementRead *node);
	virtual void visit(NodeStatementWhile *node);

	virtual void visit(NodeExp *node);

	virtual void visit(NodeExp2Exp *node);
	virtual void visit(NodeExp2IdentifierIndex *node);
	virtual void visit(NodeExp2Integer *node);
	virtual void visit(NodeExp2NegativeExp *node);
	virtual void visit(NodeExp2NotExp *node);

	virtual void visit(NodeIndex *node);

	virtual void visit(NodeOpExp *node);

	virtual void visit(NodeOp *node);

	virtual void visit(NodeIdentifier *node);
	virtual void visit(NodeInteger *node);
};

#endif
