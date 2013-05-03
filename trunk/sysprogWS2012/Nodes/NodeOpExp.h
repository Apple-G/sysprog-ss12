#ifndef NodeOpExp_H_
#define NodeOpExp_H_

#include "Node.h"
#include "NodeOp.h"
/**
   Abbildung des Knotens OP_EXP der Sprache der Aufgabenstellung.


*/

class NodeExp;

class NodeOpExp : public Node {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeExp* expression;
	NodeOp* operation;

public:
	/** Erzeugt einen neuen Knoten und setzt seine Nachfolger auf 0. */
	NodeOpExp(void) {
		expression = 0;
		operation = 0;
	}

	/** Loescht den Knoten, seine Elemente und Nachfolger. */
	virtual ~NodeOpExp(void) {
		//delete expression;
		delete operation;
	}

	/** Laesst einen Visitor zugreifen. */
	virtual void accept(Visitor* visitor) {
	  visitor->visit(this);
	}

	virtual NodeExp* getExpression() {
		return this->expression;
	}

	virtual NodeOp* getOperation() {
		return this->operation;
	}

	virtual void addChild(NodeExp* newExpression) {
		this->expression = newExpression;
	}

	virtual void addChild(NodeOp* newOperation) {
		this->operation = newOperation;
	}

	virtual void dump() {
		std::cout << typeid(this).name() << std::endl;
	}
};

#endif /* NodeOpExp_H_ */
