#ifndef NodeIdentifier_H_
#define NodeIdentifier_H_

#include "NodeLeaf.h"
#include "../SymbolTable/SymbolTable.h"

/**
   Abbildung des Knotens IDENTIFIER der Sprache der Aufgabenstellung.


*/
class NodeIdentifier : public NodeLeaf {
	/** Zugehoeriger Symboltabelleneintrag des Identifiers. */
	SymbolTable *symtabEntry;

public:
	/** Erzeugt einen neuen Knoten, der mit einem Identifier verkn�pft ist..
	@param information Informationen �ber den Identifier.
	@param line Zeile, in der der Identifier im Code steht.
	@param column Spalte, in der der Identifier im Code steht.
	@param symtabEntry Zum Identifier geh�render Symboltabelleneintrag f�r schnellen Zugriff.
	*/
	NodeIdentifier(Information *information, int line, int column, SymbolTable *symtabEntry) {
		this->line = line;
		this->column = column;
		this->information = information;
		this->symtabEntry = symtabEntry;
	}

	virtual ~NodeIdentifier(void) {
	}

	virtual void accept(Visitor* visitor) {
		//ToDo: visitor->visit(this);
	}

	virtual void dump() {
		cout << typeid(this).name() << endl;
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
