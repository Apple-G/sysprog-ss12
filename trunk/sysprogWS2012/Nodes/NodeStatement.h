#pragma once
#include "Node.h"

/**
   Abbildung des Knotens STATEMENT als Interface/abstract der Sprache der Aufgabenstellung.


*/
class NodeStatement : public Node {
protected:
	/** Erzeugt einen neuen Knoten und setzt seine Nachfolger auf 0. */
	NodeStatement(void) {
		
	}
public:
	/** Loescht den Knoten, seine Elemente und Nachfolger. */
	virtual ~NodeStatement(void) {
	}

	/** Laesst einen Visitor zugreifen. */
	virtual void accept(Visitor* visitor) = 0;

	virtual void dump() = 0;
};