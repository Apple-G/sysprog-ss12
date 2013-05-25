#ifndef NodeExp2_H_
#define NodeExp2_H_

#include "Node.h"



/**
   Abbildung des Knotens EXP2 der Sprache der Aufgabenstellung als abstrakte Klasse.


*/
class NodeExp2 : public Node {
protected:
	NodeExp2(void) {
		
	}

public:
	virtual ~NodeExp2(void) {

	}

	virtual void accept(Visitor* visitor) = 0;

};

#endif
