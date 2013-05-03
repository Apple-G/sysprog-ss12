#ifndef NodeStatementBlock_H_
#define NodeStatementBlock_H_

/**
 Abbildung des Knotens {} der Sprache der Aufgabenstellung.


 */

#include "NodeStatements.h"

//class NodeStatements;
class NodeStatementBlock: public NodeStatement {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeStatements* statements;

public:
	/** Erzeugt einen neuen Knoten und setzt seine Nachfolger auf 0. */
	NodeStatementBlock(void) {
		statements = 0;
	}

	/** Loescht den Knoten, seine Elemente und Nachfolger. */
	virtual ~NodeStatementBlock(void) {
		//delete statements;
	}

	/** Laesst einen Visitor zugreifen. */
	virtual void accept(Visitor* visitor) {
	  visitor->visit(this);
	}
	virtual NodeStatements* getStatements() {
		return this->statements;
	}

	virtual void addChild(NodeStatements* newStatements) {
		this->statements = newStatements;
	}

	virtual  void dump() {
		std::cout << typeid(this).name() << std::endl;
		if (statements != 0) {
			this->statements->dump();
		}
	}
};

#endif /* NodeStatementBlock_H_ */
