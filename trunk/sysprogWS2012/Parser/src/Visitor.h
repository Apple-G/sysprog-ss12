#ifndef Visitor_H_
#define Visitor_H_
/**
   Beschreibung des Visitor-Interfaces fuer eine baumartige Struktur von Programmanweisungen,
   welche vom Parser erzeugt wurde.

*/
//#include "../Nodes/Node.h"
class Node;
// Vorw�rtsdeklaration wegen Cross-Include
// Vorw�rtsdeklaration, damit die Datentypen in der Header verwendet werden k�nnen
// unterhalb folgen Includes
class NodeProg;
class NodeDecls;
class NodeDecl;
class NodeArray;
class NodeStatements;
class NodeStatement;
class NodeStatementAssign;
class NodeStatementBlock;
class NodeStatementIfElse;
class NodeStatementPrint;
class NodeStatementRead;
class NodeStatementWhile;
class NodeExp;
class NodeExp2;
class NodeExp2Exp;
class NodeExp2IdentifierIndex;
class NodeExp2Integer;
class NodeExp2NegativeExp;
class NodeExp2NotExp;
class NodeIndex;
class NodeOpExp;
class NodeOp;

class NodeLeaf;
class NodeIdentifier;
class NodeInteger;

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

#include "../../Nodes/NodeProg.h"
#include "../../Nodes/NodeDecls.h"
#include "../../Nodes/NodeDecl.h"
#include "../../Nodes/NodeArray.h"
#include "../../Nodes/NodeStatements.h"
#include "../../Nodes/NodeStatement.h"
#include "../../Nodes/NodeStatementAssign.h"
#include "../../Nodes/NodeStatementBlock.h"
#include "../../Nodes/NodeStatementIfElse.h"
#include "../../Nodes/NodeStatementPrint.h"
#include "../../Nodes/NodeStatementRead.h"
#include "../../Nodes/NodeStatementWhile.h"
#include "../../Nodes/NodeExp.h"
#include "../../Nodes/NodeExp2.h"
#include "../../Nodes/NodeExp2Exp.h"
#include "../../Nodes/NodeExp2IdentifierIndex.h"
#include "../../Nodes/NodeExp2Integer.h"
#include "../../Nodes/NodeExp2NegativeExp.h"
#include "../../Nodes/NodeExp2NotExp.h"
#include "../../Nodes/NodeIndex.h"
#include "../../Nodes/NodeOpExp.h"
#include "../../Nodes/NodeOp.h"

#endif
