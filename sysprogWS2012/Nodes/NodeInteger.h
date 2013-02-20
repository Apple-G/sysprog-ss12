#ifndef NodeInteger_H_
#define NodeInteger_H_

#include "NodeLeaf.h"

/**
   Abbildung des Knotens integer der Sprache der Aufgabenstellung.


*/
class NodeInteger : public NodeLeaf {
	long value;
public:
	/** Erzeugt einen neuen Knoten, der eine Ganzzahl repr�sentiert.
	@param value
	@param line Zeile, in der die Zahl im Original steht.
	@param column Spalte, in der die Zahl im Original steht.
	*/
	NodeInteger(long value, int line, int column) {
		this->value = value;
		this->line = line;
		this->column = column;
	}

	virtual ~NodeInteger(void) {
	}

	virtual void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	}

	virtual void dump() {
		std::cout << typeid(this).name() << std::endl;
	}

	virtual long getValue() {
		return value;
	}
};

#endif /* NodeInteger_H_ */
