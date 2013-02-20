#ifndef NODEDECL_H_
#define NODEDECL_H_

#include "Node.h"

/**
   Abbildung des Knotens DECL der Sprache der Aufgabenstellung.


*/
class NodeDecl : public Node {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeArray* arrayAccess;
	NodeIdentifier* identifier;

public:
	NodeDecl(void) {
		arrayAccess = 0;
		identifier = 0;
	}

	virtual ~NodeDecl(void) {
		delete arrayAccess;
		delete identifier;
	}

	virtual void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	}

	virtual NodeIdentifier* getIdentifier() {
		return this->identifier;
	}

	virtual NodeArray* getArray() {
		return this->arrayAccess;
	}

	virtual void addChild(NodeArray* newArray) {
		this->arrayAccess = newArray;
	}

	virtual void addChild(NodeIdentifier* identifier) {
		this->identifier = identifier;
	}

	virtual void dump() {
		cout << typeid(this).name() << endl;
	}
};
#endif
