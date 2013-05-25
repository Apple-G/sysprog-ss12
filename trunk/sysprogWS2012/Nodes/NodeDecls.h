#ifndef NodeDecls_H_
#define NodeDecls_H_

#include "Node.h"
/**
 Abbildung des Knotens DECLS der Sprache der Aufgabenstellung.


 */
class NodeDecls: public Node {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeDecl* declaration;
	NodeDecls* nextDeclarations;

public:
	NodeDecls(void) {
		//cout << "NodeDecls Constructor called!" << endl;
		declaration = 0;
		nextDeclarations = 0;
	}

	virtual ~NodeDecls(void) {
//		delete declaration;
//		delete nextDeclarations;
	}

	virtual void accept(Visitor* visitor) {
	  visitor->visit(this);
	}

	virtual NodeDecl* getDeclaration() {
		return this->declaration;
	}

	virtual NodeDecls* getNextDeclarations() {
		return this->nextDeclarations;
	}

	virtual void addChild(NodeDecl* newDeclaration) {
		this->declaration = newDeclaration;
	}

	virtual void addChild(NodeDecls* newDeclarations) {
		this->nextDeclarations = newDeclarations;
	}


};

#endif
