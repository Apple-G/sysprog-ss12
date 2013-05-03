#ifndef Visitor_H_
#define Visitor_H_
/**
   Beschreibung des Visitor-Interfaces fuer eine baumartige Struktur von Programmanweisungen,
   welche vom Parser erzeugt wurde.

*/
class Node;
// Vorw�rtsdeklaration wegen Cross-Include
// Vorw�rtsdeklaration, damit die Datentypen in der Header verwendet werden k�nnen
// unterhalb folgen Includes
extern class NodeProg;
extern class NodeDecls;
extern class NodeDecl;
extern class NodeArray;
extern class NodeStatements;
extern class NodeStatement;
extern class NodeStatementAssign;
extern class NodeStatementBlock;
extern class NodeStatementIfElse;
extern class NodeStatementPrint;
extern class NodeStatementRead;
extern class NodeStatementWhile;
extern class NodeExp;
extern class NodeExp2;
extern class NodeExp2Exp;
extern class NodeExp2IdentifierIndex;
extern class NodeExp2Integer;
extern class NodeExp2NegativeExp;
extern class NodeExp2NotExp;
extern class NodeIndex;
extern class NodeOpExp;
extern class NodeOp;

extern class NodeLeaf;
extern class NodeIdentifier;
extern class NodeInteger;

class Visitor {

protected:
	bool operationsSuccessful;

public:
	virtual ~Visitor(void);

	virtual bool completedWithoutErrors(void);

	virtual void visit(NodeProg *node) = 0;
	
	virtual void visit(NodeDecls *node) = 0;
	virtual void visit(NodeDecl *node) = 0;

	virtual void visit(NodeArray *node) = 0;

	virtual void visit(NodeStatements *node) = 0;
	virtual void visit(NodeStatementAssign *node) = 0;
	virtual void visit(NodeStatementBlock *node) = 0;
	virtual void visit(NodeStatementIfElse *node) = 0;
	virtual void visit(NodeStatementPrint *node) = 0;
	virtual void visit(NodeStatementRead *node) = 0;
	virtual void visit(NodeStatementWhile *node) = 0;

	virtual void visit(NodeExp *node) = 0;

	virtual void visit(NodeExp2Exp *node) = 0;
	virtual void visit(NodeExp2IdentifierIndex *node) = 0;
	virtual void visit(NodeExp2Integer *node) = 0;
	virtual void visit(NodeExp2NegativeExp *node) = 0;
	virtual void visit(NodeExp2NotExp *node) = 0;

	virtual void visit(NodeIndex *node) = 0;

	virtual void visit(NodeOpExp *node) = 0;

	virtual void visit(NodeOp *node) = 0;

	virtual void visit(NodeIdentifier *node) = 0;
	virtual void visit(NodeInteger *node) = 0;
};

#include "../Nodes/NodeProg.h"
#include "../Nodes/NodeDecls.h"
#include "../Nodes/NodeDecl.h"
#include "../Nodes/NodeArray.h"
#include "../Nodes/NodeStatements.h"
#include "../Nodes/NodeStatement.h"
#include "../Nodes/NodeStatementAssign.h"
#include "../Nodes/NodeStatementBlock.h"
#include "../Nodes/NodeStatementIfElse.h"
#include "../Nodes/NodeStatementPrint.h"
#include "../Nodes/NodeStatementRead.h"
#include "../Nodes/NodeStatementWhile.h"

#include "../Nodes/NodeExp.h"
#include "../Nodes/NodeExp2.h"
#include "../Nodes/NodeExp2Exp.h"
#include "../Nodes/NodeExp2IdentifierIndex.h"
#include "../Nodes/NodeExp2Integer.h"
#include "../Nodes/NodeExp2NegativeExp.h"
#include "../Nodes/NodeExp2NotExp.h"

#include "../Nodes/NodeIndex.h"
#include "../Nodes/NodeOpExp.h"
#include "../Nodes/NodeOp.h"

#endif
