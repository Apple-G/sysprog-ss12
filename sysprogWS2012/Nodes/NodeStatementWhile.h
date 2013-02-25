#ifndef NodeStatementWhile_H_
#define NodeStatementWhile_H_

#include "NodeStatement.h"

/**
   Abbildung des Knotens WHILE der Sprache der Aufgabenstellung.


*/
class NodeStatementWhile : public NodeStatement {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeExp* expression;
	NodeStatement* statement;

public:
	NodeStatementWhile(void) {
		expression = 0;
		statement = 0;
	}

	virtual ~NodeStatementWhile(void) {
		delete expression;
		delete statement;
	}

//	virtual void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	//}

	virtual NodeExp* getExpression() {
		return this->expression;
	}

	virtual NodeStatement* getStatement() {
		return this->statement;
	}

	virtual void addChild(NodeExp* newExpression) {
		this->expression = newExpression;
	}

	virtual void addChild(NodeStatement* newStatement) {
		this->statement = newStatement;
	}

	virtual void dump() {
		std::cout << typeid(this).name() << std::endl;
	}
};

#endif /* NodeStatementWhile_H_ */
