#pragma once
#include "NodeLeaf.h"

/**
   Abbildung des Knotens integer der Sprache der Aufgabenstellung.


*/
class NodeInteger : public NodeLeaf {

public:
	/** Erzeugt einen neuen Knoten, der eine Ganzzahl repr�sentiert.
	@param information Informationen wie Zahl selbst und Fundstelle.
	@param line Zeile, in der die Zahl im Original steht.
	@param column Spalte, in der die Zahl im Original steht.
	*/
	NodeInteger(Information *information, int line, int column) {
		this->information = information;
		this->line = line;
		this->column = column;
	}

	virtual ~NodeInteger(void) {
	}

	virtual void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	}

	virtual void dump() {
		cout << typeid(this).name() << endl;
	}

	virtual long getValue() {
		return this->information->getValue();
	}
};