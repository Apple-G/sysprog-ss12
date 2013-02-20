#pragma once
#include "NodeExp2.h"

/**
   Abbildung des Knotens EXP2 IDENTIFIER INDEX der Sprache der Aufgabenstellung.


*/
class NodeExp2IdentifierIndex : public NodeExp2 {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeIdentifier* identifier;
	NodeIndex* index;

public:
	NodeExp2IdentifierIndex(void) {
		identifier = 0;
		index = 0;
	}

	virtual ~NodeExp2IdentifierIndex(void) {
		delete identifier;
		delete index;
	}

	virtual void accept(Visitor* visitor) {
		visitor->visit(this);
	}

	virtual NodeIdentifier* getIdentifier() {
		return this->identifier;
	}

	virtual NodeIndex* getIndex() {
		return this->index;
	}

	virtual void addChild(NodeIdentifier* identifier) {
		this->identifier = identifier;
	}

	virtual void addChild(NodeIndex* newIndex) {
		this->index = newIndex;
	}

	virtual void dump() {
		cout << typeid(this).name() << endl;
	}
};