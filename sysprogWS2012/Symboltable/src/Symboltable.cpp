#include "Symboltable.h"
#include "Setup.h"
#include <string.h>


Symboltable::Symboltable()
{
	this->hashTable = new List<SymboltableEntry*> [SIZE_OF_HASHTABLE];
	this->hashTableFree = SIZE_OF_HASHTABLE;
	this->stringTable = new char [SIZE_OF_STRINGTAB];
	this->stringTablePtr = this->stringTable;
	this->stringTableFree = SIZE_OF_STRINGTAB;
}

Symboltable::~Symboltable()
{
	delete [] this->hashTable;
}

int Symboltable::hashCode(const char* lexem, int length)
{
	int hashCode = (int) ( 16 * lexem[0] + 8 * lexem[length - 1] + length );
	return hashCode % SIZE_OF_HASHTABLE;
}

int Symboltable::getSymTabFree() const
{
	return this->stringTableFree;
}

int Symboltable::getHashTabFree() const
{
	return this->hashTableFree;
}

void Symboltable::initSymbols()
{
	insert("read",TokenTypes::READ);
	insert("print",TokenTypes::PRINT);
}

int Symboltable::insert(const char* lexem, TokenTypes::TokenType tokenType)
{
	int lexemLength = strlen(lexem);
	int pos = hashCode(lexem, lexemLength);

	if (lookup(lexem) == 0)
	{
		SymboltableEntry* entry = new SymboltableEntry(this->stringTablePtr, tokenType);
		hashTable[pos].pushBack(entry);
		memcpy(this->stringTablePtr, lexem, lexemLength);
		this->stringTablePtr += lexemLength;
		*this->stringTablePtr = '\0';
		this->stringTablePtr++;

		this->stringTableFree = this->stringTableFree - (lexemLength + 1);

		this->hashTableFree--;
	}
	return pos;
}

SymboltableEntry* Symboltable::lookup(const char* lexem)
{
	int lexemLength = strlen(lexem);
	int pos = hashCode(lexem, lexemLength);

	if (hashTable[pos].getSize() != 0)
	{
		if( hashTable[pos].front()->getData() != 0)
		{
			if(strcmp(lexem, (*hashTable[pos].front()).getData()->getLexem()) == 0)
			{
				return hashTable[pos].front()->getData();
			}
			else
			{
				for (int i = 0; i < hashTable[pos].getSize(); i++)
				{
					if (hashTable[pos].getElementAt(i) != 0)
					{
						if (strcmp(lexem, hashTable[pos].getElementAt(i)->getLexem()) == 0)
						{
							return hashTable[pos].getElementAt(i);
						}
					}
				}
				return 0;
			}
		}
	}
	return 0;
}
