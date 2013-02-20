#pragma once
#include "NodeLeaf.h"
#include "SymboltableEntry.h"

/**
   Abbildung des Knotens IDENTIFIER der Sprache der Aufgabenstellung.


*/
class NodeIdentifier : public NodeLeaf {
	/** Zugehoeriger Symboltabelleneintrag des Identifiers. */
	SymboltableEntry *symtabEntry;

public:
	/** Erzeugt einen neuen Knoten, der mit einem Identifier verknüpft ist..
	@param line Zeile, in der der Identifier im Code steht.
	@param column Spalte, in der der Identifier im Code steht.
	@param symtabEntry Zum Identifier geh�render Symboltabelleneintrag für schnellen Zugriff.
	*/
	NodeIdentifier(int line, int column, SymboltableEntry *symtabEntry) {
		this->line = line;
		this->column = column;
		this->symtabEntry = symtabEntry;
	}

	virtual ~NodeIdentifier(void) {
	}

	virtual void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	}

	virtual void dump() {
		std::cout << typeid(this).name() << std::endl;
	}

	/** Stellt den Datentyp des Identifiers ein.
	@param newType Entsprechender Datentyp.
	*/
	virtual void setType(Node::TYPES newType) {
		this->information->setType(newType);
	}

	virtual Node::TYPES getType() {
		return (Node::TYPES) this->information->getType();
	}

	/** Gibt Zeiger auf Bezeichner des Identifiers zur�ck.
	@return Nullterminierter C-String.
	*/
	virtual char* getLexem() {
		return symtabEntry->getLexem(this->information);
	}
};

#endif /* NodeIdentifier_H_ */
