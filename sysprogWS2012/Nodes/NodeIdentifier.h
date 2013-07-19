#ifndef NodeIdentifier_H_
#define NodeIdentifier_H_
#include "NodeLeaf.h"
#include "../Symboltable/src/SymboltableEntry.h"

/**
   Abbildung des Knotens IDENTIFIER der Sprache der Aufgabenstellung.


*/
class NodeIdentifier : public NodeLeaf {
	SymboltableEntry *entry;/** Zugehoeriger Symboltabelleneintrag des Identifiers. */
	char *lexem;
	Node::TYPES tempType;

public:
	/** Erzeugt einen neuen Knoten, der mit einem Identifier verknüpft ist..
	@param line Zeile, in der der Identifier im Code steht.
	@param column Spalte, in der der Identifier im Code steht.
	@param symtabEntry Zum Identifier geh�render Symboltabelleneintrag für schnellen Zugriff.
	*/

	NodeIdentifier(int line, int column, char *lexem, SymboltableEntry *entry) {
		this->line = line;
		this->column = column;
		this->lexem = lexem;
		this->entry = entry;
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
		this->tempType = newType;
		switch (this->tempType) {
			case Node::TYPE_NONE:
				this->entry->setTokenType(Token::TYPE_NONE);
				break;
			case Node::TYPE_INTEGER:
				this->entry->setTokenType(Token::IDENTIFIER);
				break;
			case Node::TYPE_INTEGER_ARRAY:
				this->entry->setTokenType(Token::IDENTIFIER_ARRAY);
				break;
			case Node::TYPE_ERROR:
				this->entry->setTokenType(Token::UNKNOWN);
				break;
		}
	}

	virtual Node::TYPES getType() {
		switch (this->entry->getTokenType()) {
			case Token::TYPE_NONE:
				return Node::TYPE_NONE;
			case Token::IDENTIFIER:
				return Node::TYPE_INTEGER;
			case Token::IDENTIFIER_ARRAY:
				return Node::TYPE_INTEGER_ARRAY;
			case Token::UNKNOWN:
				return Node::TYPE_ERROR;
			default:
				return this->tempType;
		}
	}

	/** Gibt Zeiger auf Bezeichner des Identifiers zur�ck.
	@return Nullterminierter C-String.
	*/
	virtual char* getLexem() {
		return this->lexem;
	}
};

#endif /* NodeIdentifier_H_ */
