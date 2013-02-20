#ifndef NodeExp2Exp_H_
#define NodeExp2Exp_H_

#include "NodeExp2.h"

/**
   Abbildung des Knotens EXP2 EXP der Sprache der Aufgabenstellung.


*/
class NodeExp2Exp : public NodeExp2 {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeExp* expression;

public:
	NodeExp2Exp(void) {
		expression = 0;
	}

	virtual ~NodeExp2Exp(void) {
		delete expression;
	}

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
		std::cout << typeid(this).name() << std::endl;
	}
};

#endif
