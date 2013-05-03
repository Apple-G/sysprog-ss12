#ifndef NodeExp2Integer_H_
#define NodeExp2Integer_H_

#include "NodeExp2.h"

/**
   Abbildung des Knotens EXP2 integer der Sprache der Aufgabenstellung.


*/
class NodeExp2Integer : public NodeExp2 {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeInteger* integer;

public:
	NodeExp2Integer(void) {
		integer = 0;
	}

	virtual ~NodeExp2Integer(void) {
		delete integer;
	}

	virtual void accept(Visitor* visitor) {
	  visitor->visit(this);
	}

	virtual NodeInteger* getInteger() {
		return this->integer;
	}

	virtual void addChild(NodeInteger* integer) {
		this->integer = integer;
	}

	virtual void dump() {
		std::cout << typeid(this).name() << std::endl;
	}
};

#endif
