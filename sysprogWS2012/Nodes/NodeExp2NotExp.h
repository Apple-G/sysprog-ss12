#ifndef NodeExp2NotExp_H_
#define NodeExp2NotExp_H_

#include "NodeExp2.h"

/**
   Abbildung des Knotens EXP2 !EXP der Sprache der Aufgabenstellung.


*/
class NodeExp2NotExp : public NodeExp2 {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeExp2* expression;

public:
	NodeExp2NotExp(void) {
		expression = 0;
	}

	virtual ~NodeExp2NotExp(void) {
		delete expression;
	}

	//virtual void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	//}

	virtual NodeExp2* getExpression() {
		return this->expression;
	}

	virtual void addChild(NodeExp2* newExpression) {
		this->expression = newExpression;
	}

	virtual void dump() {
		std::cout << typeid(this).name() << std::endl;
	}
};

#endif
