#include "TypeCheckVisitor.h"
#include <iostream>
using namespace std;

TypeCheckVisitor::TypeCheckVisitor() {
	this->writer = NULL;
	errorCount = 0;
	operationsSuccessful = true;
}

TypeCheckVisitor::TypeCheckVisitor(Buffer *writer) {
	this->writer = writer;
	errorCount = 0;
	operationsSuccessful = true;
}


TypeCheckVisitor::~TypeCheckVisitor(void) {
}
/*
void TypeCheckVisitor::flushError(void) {
	// Write to out - either custom buffer or stderr
	if (this->writer) {
		this->writer->writeMessage(this->errorMessage);
	}
	else {
		fputs(errorMessage, stderr);
	}
}
*/
void TypeCheckVisitor::outputError(char *message, unsigned int line, unsigned int column, char *lexem) {
	/*operationsSuccessful = false;
	errorCount++;

	// Build message
	int written = sprintf(errorMessage, "%s in line %u, column %u", message, line, column);

	if (lexemLength) {
		strcpy(errorMessage + written, ", identifier: ");
		written += sizeof(", identifier: ") - 1;
		strncpy(errorMessage + written, lexem, lexemLength);
		written += lexemLength;
	}

	errorMessage[written]     = '\n';
	errorMessage[written + 1] = 0;

	// Write message
	this->flushError();
	*/
	if (lexem != NULL)
	{
		printf("%s in line %u, column %u, identifier: %s" , message, line, column, lexem);
	}else {
		printf("%s in line %u, column %u", message, line, column);
	}
}

/**
	Startaufruf f�r Programm
*/
// typeCheck (PROG ::= DECLS STATEMENTS)
void TypeCheckVisitor::visit(NodeProg *node) {
	// DECLS Typ bestimmen wenn DECLS vorhanden
	//if (node->getDeclarations())
	//	node->getDeclarations()->accept(this);

	// STATEMENTS Typ bestimmen wenn STATEMENTS vorhanden
	//if (node->getStatements())
	//	node->getStatements()->accept(this);

	// Typ von Prog ist NONE, es gibt keinen R�ckgabetyp
	node->setType(Node::TYPE_NONE);

	/* Ausgabe: Keine Fehler oder Anzahl der Fehler */
	// Write to out - either custom buffer or stderr
	if (this->operationsSuccessful) {
		sprintf(errorMessage, "No errors found, TypeCheck completed successfully.");
	}
	else {
		sprintf(errorMessage, "\n- - - - - - - - - - - -\n%u errors found, please read the log above.\nHint: Start at the top, because some errors might be consequences of errors detected before.", this->errorCount);
	}
}

/**
	
*/
void TypeCheckVisitor::visit(NodeDecls *node) {
	// DECL Typ bestimmen
	if (node->getDeclaration())
		node->getDeclaration()->accept(this);

	// Nachfolgende DECLS Typen bestimmen
	if (node->getNextDeclarations())
		node->getNextDeclarations()->accept(this);

	// Typ von DECLS ist NONE, es gibt keinen R�ckgabetyp
	node->setType(Node::TYPE_NONE);
}

/**
	Eine einzelne Deklaration: // int ARRAY identifier
*/
void TypeCheckVisitor::visit(NodeDecl *node) {
	// Haengt ein ARRAY Node dran? Zuerst pruefen
	NodeIdentifier *identifier = node->getIdentifier();
	NodeArray *arr = node->getArray();

	if (arr != NULL)
		arr->accept(this);

	// Typ des Identifiers schon definiert oder fehlerhaft?
	if (identifier->getType() != Node::TYPE_NONE) {
		outputError("identifier already defined", identifier->getLine(), identifier->getColumn());
		node->setType(Node::TYPE_ERROR);
	}
	else if (arr != NULL && arr->getType() == Node::TYPE_ERROR){
		outputError("erronous declaration of identifier", identifier->getLine(), identifier->getColumn(), identifier->getLexem());
		identifier->setType(Node::TYPE_ERROR);
		node->setType(Node::TYPE_ERROR);
	}
	else {
		// Typ auf None setzen, da wir Identifier-Deklarationen haben und keine Rueckgaben in dem Sinne
		node->setType(Node::TYPE_NONE);

		// Typ-Information speichern - entweder Array oder Standard Integer
		if (arr != NULL && arr->getType() == Node::TYPE_ARRAY) {
			identifier->setType(Node::TYPE_INTEGER_ARRAY);
		}
		else {
			identifier->setType(Node::TYPE_INTEGER);
		}
	}
}

void TypeCheckVisitor::visit(NodeArray *node) {
	// ARRAY ohne Integer bedeutet Syntax Fehler, also muss ein Integer vorhanden sein
	if (node->getInteger()->getValue() > 0) {
		node->setType(Node::TYPE_ARRAY);
	}
	else {
		outputError("no valid dimension", node->getInteger()->getLine(), node->getInteger()->getColumn());
		node->setType(Node::TYPE_ERROR);
	}
}

void TypeCheckVisitor::visit(NodeStatements *node) {
	// Explizites Visit des Statement Nodes nicht noetig -> abstrakte Klasse, es wird direkt die Methode des erbenden angesprungen
	node->getStatement()->accept(this);

	if (node->getStatements())
		node->getStatements()->accept(this);

	node->setType(Node::TYPE_NONE);
}

void TypeCheckVisitor::visit(NodeStatementAssign *node) {
	// Temp. Variablen fuer uebersichtlichere Anweisungen unterhalb
	NodeIndex *index = node->getIndex();
	NodeIdentifier *identifier = node->getIdentifier();
	NodeExp *exp = node->getExpression();

	exp->accept(this);
	if (index != NULL)
		index->accept(this);
	
	if (identifier->getType() == Node::TYPE_NONE) {
		outputError("identifier not defined", identifier->getLine(), identifier->getColumn(), identifier->getLexem());
		node->setType(Node::TYPE_ERROR);
	}
	else if (exp->getType() == Node::TYPE_INTEGER && (
				(identifier->getType() == Node::TYPE_INTEGER && index == NULL)
				|| (identifier->getType() == Node::TYPE_INTEGER_ARRAY && (index != NULL && index->getType() == Node::TYPE_ARRAY)))) {
		node->setType(Node::TYPE_NONE);
	}
	else {
		outputError("incompatible types", identifier->getLine(), identifier->getColumn(), identifier->getLexem());
		node->setType(Node::TYPE_ERROR);
	}
}

void TypeCheckVisitor::visit(NodeStatementBlock *node) {
	if (node->getStatements())
		node->getStatements()->accept(this);

	node->setType(Node::TYPE_NONE);
}

void TypeCheckVisitor::visit(NodeStatementIfElse *node) {
	node->getExpression()->accept(this);
	node->getIfStatement()->accept(this);
	node->getElseStatement()->accept(this);

	if (node->getExpression()->getType() == Node::TYPE_ERROR) {
		node->setType(Node::TYPE_ERROR);
	}
	else
		node->setType(Node::TYPE_NONE);
}

void TypeCheckVisitor::visit(NodeStatementPrint *node) {
	node->getExpression()->accept(this);
	node->setType(Node::TYPE_NONE);
}

void TypeCheckVisitor::visit(NodeStatementRead *node) {
	// Temp. Variablen fuer uebersichtlichere Anweisungen unterhalb
	NodeIndex *index = node->getIndex();
	NodeIdentifier *identifier = node->getIdentifier();

	if (identifier->getType() == Node::TYPE_NONE) {
		outputError("identifier not defined", identifier->getLine(), identifier->getColumn(), identifier->getLexem());
		node->setType(Node::TYPE_ERROR);
	}
	else if (((identifier->getType() == Node::TYPE_INTEGER) && index == NULL)
		|| ((identifier->getType() == Node::TYPE_INTEGER_ARRAY) && (index != NULL && index->getType() == Node::TYPE_ARRAY)))
		node->setType(Node::TYPE_NONE);
	else {
		outputError("incompatible types", identifier->getLine(), identifier->getColumn(), identifier->getLexem());
		node->setType(Node::TYPE_ERROR);
	}
}

void TypeCheckVisitor::visit(NodeStatementWhile *node) {
	node->getExpression()->accept(this);
	node->getStatement()->accept(this);

	if (node->getExpression()->getType() == Node::TYPE_ERROR)
		node->setType(Node::TYPE_ERROR);
	else
		node->setType(Node::TYPE_NONE);
}

void TypeCheckVisitor::visit(NodeExp* node) {
	node->getExpression()->accept(this);

	if (node->getOperatorExpression() != NULL)
		node->getOperatorExpression()->accept(this);

	if (node->getOperatorExpression() == NULL)
		node->setType(node->getExpression()->getType());
	else if(node->getExpression()->getType() != node->getOperatorExpression()->getType())
		node->setType(Node::TYPE_ERROR);
	else
		node->setType(node->getExpression()->getType());

}

void TypeCheckVisitor::visit(NodeExp2Exp* node) {
	node->getExpression()->accept(this);
	node->setType(node->getExpression()->getType());
}

void TypeCheckVisitor::visit(NodeExp2IdentifierIndex* node) {
	// Temp. Variablen fuer uebersichtlichere Anweisungen unterhalb
	NodeIndex *index = node->getIndex();
	NodeIdentifier *identifier = node->getIdentifier();

	if (index != NULL)
		index->accept(this);

	if(identifier->getType() == Node::TYPE_NONE) {
		outputError("identifier not defined", identifier->getLine(), identifier->getColumn(), identifier->getLexem());
		node->setType(Node::TYPE_ERROR);
	}
	else if (identifier->getType() == Node::TYPE_INTEGER && index == NULL)
		node->setType(identifier->getType());
	else if (identifier->getType() == Node::TYPE_INTEGER_ARRAY && (index != NULL && index->getType() == Node::TYPE_ARRAY))
		node->setType(Node::TYPE_INTEGER);
	else {
		outputError("no primitive Type", identifier->getLine(), identifier->getColumn(), identifier->getLexem());
		node->setType(Node::TYPE_ERROR);
	}
}

void TypeCheckVisitor::visit(NodeExp2Integer* node) {
	node->setType(Node::TYPE_INTEGER);
}

void TypeCheckVisitor::visit(NodeExp2NegativeExp* node) {
	node->getExpression()->accept(this);
	node->setType(node->getExpression()->getType());
}

void TypeCheckVisitor::visit(NodeExp2NotExp* node) {
	node->getExpression()->accept(this);

	if (node->getExpression()->getType() != Node::TYPE_INTEGER)
		node->setType(Node::TYPE_ERROR);
	else
		node->setType(Node::TYPE_INTEGER);
}


void TypeCheckVisitor::visit(NodeIndex* node) {
	node->getExpression()->accept(this);

	if(node->getExpression()->getType() == Node::TYPE_ERROR)
		node->setType(Node::TYPE_ERROR);
	else
		node->setType(Node::TYPE_ARRAY);
}

void TypeCheckVisitor::visit(NodeOpExp* node) {
	node->getOperation()->accept(this);
	node->getExpression()->accept(this);

	node->setType(node->getExpression()->getType());
}

void TypeCheckVisitor::visit(NodeOp* node) {
	// Wird bereits vom Parser erledigt statt differenzierte Klassen zu erzeugen
}

void TypeCheckVisitor::visit(NodeIdentifier *node) {
	throw 7;
}

void TypeCheckVisitor::visit(NodeInteger *node) {
	throw 42;
}
