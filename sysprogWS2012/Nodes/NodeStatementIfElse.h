#ifndef NodeStatementIfElse_H_
#define NodeStatementIfElse_H_

#include "NodeStatement.h"

/**
   Abbildung des Knotens "if STATEMENT else STATEMENT" der Sprache der Aufgabenstellung.


*/
class NodeStatementIfElse : public NodeStatement {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeExp* expression;
	NodeStatement* ifStatement;
	NodeStatement* elseStatement;

public:
	/** Erzeugt einen neuen Knoten und setzt seine Nachfolger auf 0. */
	NodeStatementIfElse(void) {
		expression = 0;
		ifStatement = 0;
		elseStatement = 0;
	}

	/** Loescht den Knoten, seine Elemente und Nachfolger. */
	virtual ~NodeStatementIfElse(void) {
		delete expression;
		delete ifStatement;
		delete elseStatement;
	}

	/** Laesst einen Visitor zugreifen. */
	virtual void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	}

	virtual NodeExp* getExpression() {
		return this->expression;
	}

	virtual NodeStatement* getIfStatement() {
		return this->ifStatement;
	}

	virtual NodeStatement* getElseStatement() {
		return this->elseStatement;
	}

	virtual void addChild(NodeExp* newExpression) {
		this->expression = newExpression;
	}

	virtual void setIfStatement(NodeStatement* newIfStatement) {
		this->ifStatement = newIfStatement;
	}

	virtual void setElseStatement(NodeStatement* newElseStatement) {
		this->elseStatement = newElseStatement;
	}

	virtual void dump() {
		cout << typeid(this).name() << endl;
	}
};

#endif /* NodeStatementIfElse_H_ */
