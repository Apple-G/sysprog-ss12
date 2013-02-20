#pragma once
#include "NodeStatement.h"

/**
   Abbildung des Knotens print() der Sprache der Aufgabenstellung.


*/
class NodeStatementPrint : public NodeStatement {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeExp* expression;

public:
	/** Erzeugt einen neuen Knoten und setzt seine Nachfolger auf 0. */
	NodeStatementPrint(void) {
		expression = 0;
	}

	/** Loescht den Knoten, seine Elemente und Nachfolger. */
	virtual ~NodeStatementPrint(void) {
		delete expression;
	}

	/** Laesst einen Visitor zugreifen. */
	virtual void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	}

	virtual NodeExp* getExpression() {
		return this->expression;
	}

	virtual void addChild(NodeExp* newExpression) {
		this->expression = newExpression;
	}

	virtual void dump() {
		cout << typeid(this).name() << endl;
	}
};