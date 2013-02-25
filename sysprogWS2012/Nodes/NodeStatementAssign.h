#ifndef NodeStatementAssign_H_
#define NodeStatementAssign_H_

#include "NodeStatement.h"

/**
   Abbildung des Knotens identifier = EXP; der Sprache der Aufgabenstellung.


*/
class NodeStatementAssign : public NodeStatement {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeIdentifier* identifier;
	NodeExp* expression;
	NodeIndex* index;

public:
	/** Erzeugt einen neuen Knoten und setzt seine Nachfolger auf 0. */
	NodeStatementAssign(void) {
		identifier = 0;
		expression = 0;
		index = 0;
	}

	/** Loescht den Knoten, seine Elemente und Nachfolger. */
	virtual ~NodeStatementAssign(void) {
		delete identifier;
		delete expression;
		delete index;
	}

	/** Laesst einen Visitor zugreifen. */
	//void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	//}

	virtual NodeIdentifier* getIdentifier() {
		return this->identifier;
	}

	virtual NodeExp* getExpression() {
		return this->expression;
	}

	virtual NodeIndex* getIndex() {
		return this->index;
	}

	virtual void addChild(NodeIdentifier* newIdentifier) {
		this->identifier = newIdentifier;
	}

	virtual void addChild(NodeExp* newExpression) {
		this->expression = newExpression;
	}

	virtual void addChild(NodeIndex* newIndex) {
		this->index = newIndex;
	}

	virtual void dump() {
		std::cout << typeid(this).name() << std::endl;
	}
};

#endif /* NodeStatementAssign_H_ */
