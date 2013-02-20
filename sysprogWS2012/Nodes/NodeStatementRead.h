#pragma once
#include "NodeStatement.h"

/**
   Abbildung des Knotens read() der Sprache der Aufgabenstellung.


*/
class NodeStatementRead : public NodeStatement {

	/** M�gliche Nachfolger oder Elemente des Knotens */
	NodeIdentifier* identifier;
	NodeIndex* index;

public:
	/** Erzeugt einen neuen Knoten und setzt seine Nachfolger auf 0. */
	NodeStatementRead(void) {
		identifier = 0;
		index = 0;
	}

	/** Loescht den Knoten, seine Elemente und Nachfolger. */
	virtual ~NodeStatementRead(void) {
		delete identifier;
		delete index;
	}

	/** Laesst einen Visitor zugreifen. */
	virtual void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	}

	/** Reicht den zugehoerigen Identifier durch.
	@return Zeiger auf den Identifier des Knotens.
	*/
	virtual NodeIdentifier* getIdentifier() {
		return this->identifier;
	}

	/** Reicht den zugehoerigen Index (Array-Index-Zugriff) weiter.
	@return Zeiger auf Index-Knoten oder Null-Pointer.
	*/
	virtual NodeIndex* getIndex() {
		return this->index;
	}

	/** Identifier-Kind-Knoten einh�ngen.
	@param newIdentifier Identifier-Knoten, der hierarchisch hierzu geh�rt.
	*/
	virtual void addChild(NodeIdentifier* newIdentifier) {
		this->identifier = newIdentifier;
	}

	/** Index (Array-Index-Zugriff) Knoten als Kind einh�ngen.
	@param newIndex Entsprechender Index-Knoten.
	*/
	virtual void addChild(NodeIndex* newIndex) {
		this->index = newIndex;
	}

	virtual void dump() {
		cout << typeid(this).name() << endl;
	}
};