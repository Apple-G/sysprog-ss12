#ifndef CodeGeneratorVisitor_H_
#define CodeGeneratorVisitor_H_
#include "Visitor.h"
#include "Buffer.h"

/**
   Dieser Visitor durchl�uft eine baumartige Struktur von Programmanweisungen, welche
   vom Parser erzeugt wurde. Entsprechend der Regeln der Sprache und der Strukturen
   werden Anweisungen f�r die Zielplatform "Sysprog-Interpreter-Runtime" erzeugt.

*/
class CodeGeneratorVisitor : public Visitor {
	/** Benutztes Ausgabeinterface, um Code wegzuschreiben. */
	Buffer *writer;

	/** Markenz�hler - wichtig f�r Rekursionen, damit sich Sprungmarken nicht wiederholen. */
	unsigned int label_count;

	/** Gr��e f�r tempor�ren Puffer f�r Erzeugen der Marken. */
	static const unsigned int MAX_LABEL_BUFFER_SIZE = 20;

	/** Erzeugt eine Sprungmarke und schreibt diese in ein char Feld.
	@param buf Hier wird das Ergebnis nullterminiert hingeschrieben.
	*/
	virtual void generateJumpLabel(char *buf);

public:
	/** Erzeugt einen neuen Visitor und initialisiert internen Zustand.
	@param writer Hierueber werden die Ausgaben weggeschrieben.
	*/
	//ToDo: CodeGeneratorVisitor::CodeGeneratorVisitor(Buffer *writer);
	CodeGeneratorVisitor(Buffer *writer);

	/** Gibt auf Heap verwendeten Speicher wieder frei. */
	virtual ~CodeGeneratorVisitor(void);

	/* Geht jeweilige Node durch und erzeugt Code entsprechend der Spezifikationen. */
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
