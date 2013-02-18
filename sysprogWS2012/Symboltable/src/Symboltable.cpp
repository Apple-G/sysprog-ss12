#include "Symboltable.h"

Symboltable::Symboltable() {
	this->hashTable = new List<SymboltableEntry*> [SIZE_OF_HASHTABLE];
	this->initSymbols();
}

Symboltable::~Symboltable() {
	delete[] this->hashTable;
}

int Symboltable::hashCode(char* lexem, int length) {
	int hashCode = (int) (16 * lexem[0] + 8 * lexem[length - 1] + length);
	return hashCode % SIZE_OF_HASHTABLE;
}

void Symboltable::initSymbols() {
	insert("read", Token::READ);
	insert("print", Token::PRINT);
}

SymboltableEntry* Symboltable::insert(char* lexem, Token::TokenType tokenType) {
	int lexemLength = CHARHELPERgetLenght(lexem);
	int pos = hashCode(lexem, lexemLength);

	SymboltableEntry* entry = lookup(lexem);

	//Lexem nicht vorhanden => Lexem eintragen
	if (entry == 0) {
		entry = new SymboltableEntry(lexem, tokenType);
		hashTable[pos].pushBack(entry);
	}
	return entry;
}

SymboltableEntry* Symboltable::lookup(char* lexem) {
	int lexemLength = CHARHELPERgetLenght(lexem);
	int pos = hashCode(lexem, lexemLength);

	if (hashTable[pos].getSize() != 0) {
		if (hashTable[pos].front()->getData() != 0) {

			for (int i = 0; i < hashTable[pos].getSize(); i++) {
				if (hashTable[pos].getElementAt(i) != 0) {
					if (CHARHELPERcompare(lexem,
							hashTable[pos].getElementAt(i)->getLexem())) {
						return hashTable[pos].getElementAt(i);
					}
				}
			}
			return 0;

		}
	}
	return 0;
}

//TODO: move to CharHelper
int Symboltable::CHARHELPERgetLenght(char* string) {
	int count = 0;
	char* temp = string;
	while (*temp != 0) {
		count++;
		temp++;
	}
	return count;
}

bool Symboltable::CHARHELPERcompare(char* a, char* b) {
	if (*a != '\0' && *b != '\0') {
		while (*a - *b == 0 && (*a != '\0' || *b != '\0')) {
			a++;
			b++;
		}
	}
	return (*a - *b) == 0;

}

