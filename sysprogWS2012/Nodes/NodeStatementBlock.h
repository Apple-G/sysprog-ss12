#ifndef NodeStatementBlock_H_
#define NodeStatementBlock_H_

#include "NodeStatement.h"

/**
   Abbildung des Knotens {} der Sprache der Aufgabenstellung.


*/
class NodeStatementBlock : public NodeStatement {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeStatements* statements;

public:
	/** Erzeugt einen neuen Knoten und setzt seine Nachfolger auf 0. */
	NodeStatementBlock(void) {
		statements = 0;
	}

	/** Loescht den Knoten, seine Elemente und Nachfolger. */
	virtual ~NodeStatementBlock(void) {
		delete statements;
	}

	/** Laesst einen Visitor zugreifen. */
	virtual void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	}

	virtual NodeStatements* getStatements() {
		return this->statements;
	}

	virtual void addChild(NodeStatements* newStatements) {
		this->statements = newStatements;
	}

	virtual void dump() {
		std::cout << typeid(this).name() << std::endl;
	}
};

#endif /* NodeStatementBlock_H_ */
