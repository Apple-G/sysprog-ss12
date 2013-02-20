#pragma once
#include "Node.h"

/**
   Abbildung des Knotens INDEX der Sprache der Aufgabenstellung.


*/
class NodeIndex : public Node {
	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeExp* expression;

public:
	NodeIndex(void) {
		expression = 0;
	}

	virtual ~NodeIndex(void) {
		delete expression;
	}

	virtual void accept(Visitor* visitor) {
		visitor->visit(this);
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