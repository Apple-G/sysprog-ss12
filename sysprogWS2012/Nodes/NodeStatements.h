#ifndef Nodestatements_H_
#define Nodestatements_H_

#include "Node.h"

#include "NodeExp.h"
#include "NodeIndex.h"

#include "NodeStatementAssign.h"
#include "NodeStatementBlock.h"
#include "NodeStatementIfElse.h"
#include "NodeStatementPrint.h"
#include "NodeStatementRead.h"
#include "NodeStatementWhile.h"

/**
   Abbildung des Knotens STATEMENTS der Sprache der Aufgabenstellung.


*/
class NodeStatements : public Node {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeStatement* statement;
	NodeStatements* nextStatements;

public:
	/** Erzeugt einen neuen Knoten und setzt seine Nachfolger auf 0. */
	NodeStatements(void) {
		//cout << "NodeStatements Constructor called!" << endl;
		statement = 0;
		nextStatements = 0;
	}

	/** Loescht den Knoten, seine Elemente und Nachfolger. */
	virtual ~NodeStatements(void) {
		delete statement;
		delete nextStatements;
	}

	/** Laesst einen Visitor zugreifen.
		@param visitor Besucher, der zugreifen soll.
	*/
	//void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	//}

	/* Node-spezifischer Code */
	virtual NodeStatement* getStatement() {
		return this->statement;
	}

	/** Gibt einen Zeiger auf den n�chsten Statements-Knoten.
	@return Statements, das der Nachfolger dieses Knotens ist.
	*/
	virtual NodeStatements* getStatements() {
		return this->nextStatements;
	}

	/** Diesem Knoten ein Statement hinzuf�gen.
	@param newStatement Statement, das zu diesem Knoten geh�rt.
	*/
	virtual void addChild(NodeStatement* newStatement) {
		this->statement = newStatement;
	}

	/** Einen nachfolgenden Statements Knoten hinzuf�gen.
	@param newStatements Nachfolgender Statements Knoten.
	*/
	virtual void addChild(NodeStatements* newStatements) {
		this->nextStatements = newStatements;
	}

	virtual void dump() {
		std::cout << typeid(this).name() << std::endl;
	}
};

#endif /* Nodestatements_H_ */
