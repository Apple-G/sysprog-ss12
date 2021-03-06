#ifndef NodeProg_H_
#define NodeProg_H_

#include "Node.h"

/**
   Abbildung des Knotens PROG der Sprache der Aufgabenstellung.


*/
class NodeProg : public Node {

	/** Mögliche Nachfolger oder Elemente des Knotens */
	NodeDecls* declarations;
	NodeStatements* statements;

public:
	/** Erzeugt einen neuen Knoten und setzt seine Nachfolger auf 0. */
	NodeProg(void) {
		//cout << "NodeProg Constructor called!" << endl;
		declarations = 0;
		statements = 0;
	}

	/** Loescht den Knoten, seine Elemente und Nachfolger. */
	virtual ~NodeProg(void) {
		delete declarations;
		delete statements;
	}

	/** Laesst einen Visitor zugreifen. */
	virtual void accept(Visitor* visitor) {
	  visitor->visit(this);
	}

	virtual NodeDecls* getDeclarations() {
		return this->declarations;
	}

	virtual NodeStatements* getStatements() {
		return this->statements;
	}

	virtual void addChild(NodeDecls* newDeclarations) {
		//cout << "*New NodeProg child: NodeDecls" << endl;
		this->declarations = newDeclarations;
	}

	virtual void addChild(NodeStatements* newStatements) {
		//cout << "*New NodeProg child: NodeStatements" << endl;
		this->statements = newStatements;
	}
};

#endif /* NodeProg_H_ */
