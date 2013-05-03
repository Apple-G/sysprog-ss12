#ifndef NodeIdentifier_H_
#define NodeIdentifier_H_
#include "NodeLeaf.h"
#include "SymboltableEntry.h"

/**
   Abbildung des Knotens IDENTIFIER der Sprache der Aufgabenstellung.


*/
class NodeIdentifier : public NodeLeaf {
	/** Zugehoeriger Symboltabelleneintrag des Identifiers. */
	char *lexem;

public:
	/** Erzeugt einen neuen Knoten, der mit einem Identifier verknüpft ist..
	@param line Zeile, in der der Identifier im Code steht.
	@param column Spalte, in der der Identifier im Code steht.
	@param symtabEntry Zum Identifier geh�render Symboltabelleneintrag für schnellen Zugriff.
	*/
	NodeIdentifier(int line, int column, char *lexem) {
		this->line = line;
		this->column = column;
		this->lexem = lexem;
	}

	virtual ~NodeIdentifier(void) {
	}

	virtual void accept(Visitor* visitor) {
	  visitor->visit(this);
	}

	virtual void dump() {
		std::cout << typeid(this).name() << std::endl;
	}

	/** Stellt den Datentyp des Identifiers ein.
	@param newType Entsprechender Datentyp.
	*/
	virtual void setType(Node::TYPES newType) {
		this->nodeType = newType;
	}

	virtual Node::TYPES getType() {
		return this->nodeType;
	}

	/** Gibt Zeiger auf Bezeichner des Identifiers zur�ck.
	@return Nullterminierter C-String.
	*/
	virtual char* getLexem() {
		return this->lexem;
	}
};

#endif /* NodeIdentifier_H_ */
