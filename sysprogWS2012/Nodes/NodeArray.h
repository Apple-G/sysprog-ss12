#ifndef NODEARRAY_H_
#define NODEARRAY_H_

#include "Node.h"

/**
   Abbildung des Knotens ARRAY der Sprache der Aufgabenstellung.


*/
class NodeArray : public Node {
	/** M�gliche Nachfolger oder Elemente des Knotens */
 	NodeInteger* integer;

public:
	NodeArray(void) {
		this->integer = 0;
	}

	virtual ~NodeArray(void) {
//		delete this->integer;
	}

	virtual void accept(Visitor* visitor) {
	  visitor->visit(this);
	}

	virtual void addChild(NodeInteger* newInteger) {
		this->integer = newInteger;
	}

	virtual NodeInteger *getInteger() {
		return this->integer;
	}

};

#endif
