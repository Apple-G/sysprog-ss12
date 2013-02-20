#ifndef NodeLeaf_H_
#define NodeLeaf_H_

#include "Node.h"
#include "../SymbolTable/Information.h"

/**
   Abbildung der Blaetter des Baumes als abstrakte Klasse.


*/
class NodeLeaf : public Node {
protected:
	/** Zugehoerige Information des Blattes. */
	Information* information;

	/** Zeile in der der originale Code steht. */
	int line;

	/** Spalte in der der originale Code steht. */
	int column;

	/** Erzeugt ein neues Blatt. */
	NodeLeaf(void) {
		this->information = 0;
	}

public:
	/* Standard: Konstruktor, Destruktor, accept */
	virtual ~NodeLeaf(void) {
		delete information;
	}

	virtual void accept(Visitor* visitor) = 0;

	/* Node-spezifischer Code */
	virtual int getLine() {
		return line;
	}

	virtual int getColumn() {
		return column;
	}

	virtual Information* getInformation() {
		return this->information;
	}

	virtual void dump() {
		cout << "Leaf: - ";
		cout << "Value: "; //this->information->getValue();
		cout << endl;
	}
};

#endif /* NodeLeaf_H_ */
