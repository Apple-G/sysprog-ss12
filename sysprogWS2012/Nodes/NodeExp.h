#ifndef NodeExp_H_
#define NodeExp_H_

#include "Node.h"

#include "NodeOpExp.h"

#include "NodeExp2Exp.h"
#include "NodeExp2IdentifierIndex.h"
#include "NodeExp2Integer.h"
#include "NodeExp2NegativeExp.h"
#include "NodeExp2NotExp.h"


/**
   Abbildung des Knotens EXP der Sprache der Aufgabenstellung.


*/
class NodeExp : public Node {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeExp2* expression;
	NodeOpExp* operatorExpression;

public:
	NodeExp(void) {
		expression = 0;
		operatorExpression = 0;
	}

	virtual ~NodeExp(void) {
		delete expression;
		delete operatorExpression;
	}

	virtual void accept(Visitor* visitor) {
	  visitor->visit(this);
	}

	virtual NodeExp2* getExpression() {
		return this->expression;
	}

	virtual NodeOpExp* getOperatorExpression() {
		return this->operatorExpression;
	}

	virtual void addChild(NodeExp2* newExpression) {
		this->expression = newExpression;
	}

	virtual void addChild(NodeOpExp* newOperatorExpression) {
		this->operatorExpression = newOperatorExpression;
	}

	virtual void dump() {
		std::cout << typeid(this).name() << std::endl;
	}
};

#endif
