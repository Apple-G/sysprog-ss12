#include "CodeGeneratorVisitor.h"
#include "CharHelper.h"
#include <iostream>
using namespace std;

CodeGeneratorVisitor::CodeGeneratorVisitor(Buffer *writer) {
	operationsSuccessful = true;
	this->writer = writer;
	this->label_count = 0;
}


CodeGeneratorVisitor::~CodeGeneratorVisitor(void) {
}

int CodeGeneratorVisitor::generateJumpLabel() {
	return label_count++;
}

void CodeGeneratorVisitor::visit(NodeProg *node) {
	// DECLS durchgehen
	//if (node->getDeclarations())
	//	node->getDeclarations()->accept(this);

	// STATEMENTS durchgehen
	//if (node->getStatements())
	//	node->getStatements()->accept(this);

	// gibt es ein statement, gibt es am ende auch ein statements ohne statement...
	if (node->getStatements())
		writer->writeMessage(" NOP");

	// Anweisungsende
	writer->writeMessage(" STP");
}

void CodeGeneratorVisitor::visit(NodeDecls *node) {
	if (node->getDeclaration())
		node->getDeclaration()->accept(this);

	if (node->getNextDeclarations())
		node->getNextDeclarations()->accept(this);
}

void CodeGeneratorVisitor::visit(NodeDecl *node) {
	NodeIdentifier *identifier = node->getIdentifier();
	NodeArray *arr = node->getArray();

	writer->writeMessage(" DS $");
	writer->writeMessage(identifier->getLexem());

	if (arr != NULL)
		arr->accept(this);
	else
		writer->writeMessage(" 1");
}

void CodeGeneratorVisitor::visit(NodeArray *node) {

	writer->writeMessage(CharHelper::convertLong(node->getInteger()->getValue()));

	/*
	alternativ nur den integer wert speichern, siehe Seite 72 bei Aufgabe 2
	*/
}

void CodeGeneratorVisitor::visit(NodeStatements *node) {
	node->getStatement()->accept(this);

	if (node->getStatements())
		node->getStatements()->accept(this);
	else
		writer->writeMessage(" NOP");
}

void CodeGeneratorVisitor::visit(NodeStatementAssign *node) {
	NodeIndex *index = node->getIndex();
	NodeIdentifier *identifier = node->getIdentifier();
	NodeExp *exp = node->getExpression();

	exp->accept(this);

	writer->writeMessage(" LA $");
	writer->writeMessage(identifier->getLexem());
	
	if (index != NULL)
		index->accept(this);

	writer->writeMessage(" STR");
}

void CodeGeneratorVisitor::visit(NodeStatementBlock *node) {
	if (node->getStatements())
		node->getStatements()->accept(this);
}

void CodeGeneratorVisitor::visit(NodeStatementIfElse *node) {
	char* label1;
	char* label2;

	label1 = CharHelper::convertInt(generateJumpLabel());
	label2 = CharHelper::convertInt(generateJumpLabel());

	node->getExpression()->accept(this);
	writer->writeMessage(" JIN #label"); // JIN #label1
	writer->writeMessage(label1);

	node->getIfStatement()->accept(this);
	writer->writeMessage(" JMP #label"); // JMP #label2
	writer->writeMessage(label2);
	writer->writeMessage(" #label"); // #label1 NOP
	writer->writeMessage(label1);
	writer->writeMessage(" NOP");

	node->getElseStatement()->accept(this);
	writer->writeMessage(" #label"); // #label2 NOP
	writer->writeMessage(label2);
	writer->writeMessage(" NOP");
}

void CodeGeneratorVisitor::visit(NodeStatementPrint *node) {
	node->getExpression()->accept(this);
	writer->writeMessage(" PRI");
}

void CodeGeneratorVisitor::visit(NodeStatementRead *node) {
	NodeIndex *index = node->getIndex();
	NodeIdentifier *identifier = node->getIdentifier();

	writer->writeMessage(" RDI");
	writer->writeMessage(" LA $");
	writer->writeMessage(identifier->getLexem());

	if (index != NULL)
		index->accept(this);

	writer->writeMessage(" STR");
}

void CodeGeneratorVisitor::visit(NodeStatementWhile *node) {
	char* label1;
	char* label2;

	label1 = CharHelper::convertInt(generateJumpLabel());
	label2 = CharHelper::convertInt(generateJumpLabel());

	writer->writeMessage(" #label"); // #label1 NOP
	writer->writeMessage(label1);
	writer->writeMessage(" NOP");

	node->getExpression()->accept(this);
	writer->writeMessage(" JIN #label"); // JIN #label2
	writer->writeMessage(label2);

	node->getStatement()->accept(this);
	writer->writeMessage(" JMP #label"); // JMP #label1
	writer->writeMessage(label1);
	writer->writeMessage(" #label"); // #label2 NOP
	writer->writeMessage(label2);
	writer->writeMessage(" NOP");
}

void CodeGeneratorVisitor::visit(NodeExp* node) {
	NodeOpExp *opExp = node->getOperatorExpression();

	if (opExp == NULL) {
		node->getExpression()->accept(this);
	}
	else if (opExp->getOperation()->getType() == Node::TYPE_OP_GREATER) {
		opExp->accept(this);
		node->getExpression()->accept(this);
		writer->writeMessage(" LSI");
	}
	else if (opExp->getOperation()->getType() == Node::TYPE_OP_UNEQUAL) {
		node->getExpression()->accept(this);
		opExp->accept(this);
		writer->writeMessage(" NOT");
	}
	else {
		node->getExpression()->accept(this);
		opExp->accept(this);
	}
}

void CodeGeneratorVisitor::visit(NodeExp2Exp* node) {
	node->getExpression()->accept(this);
}

void CodeGeneratorVisitor::visit(NodeExp2IdentifierIndex* node) {
	NodeIndex *index = node->getIndex();
	NodeIdentifier *identifier = node->getIdentifier();

	writer->writeMessage(" LA $");
	writer->writeMessage(identifier->getLexem());

	if (index != NULL)
		index->accept(this);

	writer->writeMessage(" LV");
}

void CodeGeneratorVisitor::visit(NodeExp2Integer* node) {
	writer->writeMessage(" LC ");
	writer->writeMessage(CharHelper::convertLong(node->getInteger()->getValue()));
}

void CodeGeneratorVisitor::visit(NodeExp2NegativeExp* node) {
	writer->writeMessage(" LC 0");
	node->getExpression()->accept(this);
	writer->writeMessage(" SBI");
}

void CodeGeneratorVisitor::visit(NodeExp2NotExp* node) {
	node->getExpression()->accept(this);
	writer->writeMessage(" NOT");
}


void CodeGeneratorVisitor::visit(NodeIndex* node) {
	node->getExpression()->accept(this);
	writer->writeMessage(" ADI");
}

void CodeGeneratorVisitor::visit(NodeOpExp* node) {
	node->getExpression()->accept(this);
	node->getOperation()->accept(this);
}

void CodeGeneratorVisitor::visit(NodeOp* node) {
	char *cmd;

	switch (node->getType())
	{
	case Node::TYPE_OP_PLUS:     cmd = " ADI"; break;
	case Node::TYPE_OP_MINUS:    cmd = " SBI"; break;
	case Node::TYPE_OP_MULTIPLY: cmd = " MLI"; break;
	case Node::TYPE_OP_DIVIDE:   cmd = " DVI"; break;
	case Node::TYPE_OP_SMALLER:  cmd = " LSI"; break;
	case Node::TYPE_OP_GREATER:  cmd = ""; break; // Bereits aufgeloest in CodeGeneratorVisitor::visit(NodeExp* node)
	case Node::TYPE_OP_EQUAL:    cmd = " EQI"; break;
	case Node::TYPE_OP_UNEQUAL:  cmd = " EQI"; break;// Bereits teilaufgeloest in CodeGeneratorVisitor::visit(NodeExp* node)
	case Node::TYPE_OP_AND:      cmd = " AND"; break;
	default: throw 69;
	}

	writer->writeMessage(cmd);
}

void CodeGeneratorVisitor::visit(NodeIdentifier *node) {
	throw 7;
}

void CodeGeneratorVisitor::visit(NodeInteger *node) {
	throw 42;
}
