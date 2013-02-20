#ifndef NodeOp_H_
#define NodeOp_H_

#include "NodeLeaf.h"

/**
   Abbildung des Knotens OP der Sprache der Aufgabenstellung.


*/
class NodeOp : public NodeLeaf {

public:
	/** Erzeugt einen neuen Knoten und setzt seine Nachfolger auf 0. */
	NodeOp(void) {
	}

	/** Erzeugt einen Operator Knoten direkt mit zugeordnetem Typ..
	@param type Typ/Art des Operators.
	*/
	NodeOp(Node::TYPES type) {
		this->information = 0;
		this->nodeType = type;
	}

	/** Loescht den Knoten, seine Elemente und Nachfolger. */
	virtual ~NodeOp(void) {
	}

	/** Laesst einen Visitor zugreifen.
		@param visitor Besucher, der zugreifen soll.
	*/
	virtual void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	}

	virtual void dump() {
		cout << typeid(this).name() << endl;
	}
};

#endif /* NodeOp_H_ */
