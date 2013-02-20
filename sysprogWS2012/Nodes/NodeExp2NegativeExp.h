#pragma once
#include "NodeExp2.h"

/**
   Abbildung des Knotens EXP2 -EXP der Sprache der Aufgabenstellung.


*/
class NodeExp2NegativeExp : public NodeExp2 {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeExp* expression;

public:
	NodeExp2NegativeExp(void) {
		expression = 0;
	}

	virtual ~NodeExp2NegativeExp(void) {
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