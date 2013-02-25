#ifndef NodeLeaf_H_
#define NodeLeaf_H_

#include "Node.h"

/**
   Abbildung der Blaetter des Baumes als abstrakte Klasse.


*/
class NodeLeaf : public Node {
protected:

	/** Zeile in der der originale Code steht. */
	int line;

	/** Spalte in der der originale Code steht. */
	int column;

	/** Erzeugt ein neues Blatt. */
	NodeLeaf(void) {
	}

public:
	/* Standard: Konstruktor, Destruktor, accept */
	virtual ~NodeLeaf(void) {
	}

	//virtual void accept(Visitor* visitor) = 0;

	/* Node-spezifischer Code */
	virtual int getLine() {
		return line;
	}

	virtual int getColumn() {
		return column;
	}

	virtual void dump() {
	}
};

#endif /* NodeLeaf_H_ */
