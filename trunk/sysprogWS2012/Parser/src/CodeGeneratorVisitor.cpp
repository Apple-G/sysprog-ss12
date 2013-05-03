#include "CodeGeneratorVisitor.h"
#include <iostream>
using namespace std;

CodeGeneratorVisitor::CodeGeneratorVisitor(OutputBuffer *writer) {
	operationsSuccessful = true;
	this->writer = writer;
	this->marken = 0;
}


CodeGeneratorVisitor::~CodeGeneratorVisitor(void) {
}

void CodeGeneratorVisitor::generateJumpLabel(char *buf) {
	ltoa(marken, buf, 10);
	marken++;
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
		writer->writeCharsUnchecked(" NOP");

	// Anweisungsende
	writer->writeCharsUnchecked(" STP");
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

	writer->writeCharsUnchecked(" DS ");
	writer->writeChars(identifier->getInformation()->getLength(), identifier->getLexem());

	if (arr != NULL)
		arr->accept(this);
	else
		writer->writeCharsUnchecked(" 1");
}

void CodeGeneratorVisitor::visit(NodeArray *node) {
	char temp[30];
	temp[0] = ' ';
	ltoa(node->getInteger()->getValue(), temp + 1, 10);
	writer->writeCharsUnchecked(temp);

	/*
	alternativ nur den integer wert speichern, siehe Seite 72 bei Aufgabe 2
	*/
}

void CodeGeneratorVisitor::visit(NodeStatements *node) {
	node->getStatement()->accept(this);

	if (node->getStatements())
		node->getStatements()->accept(this);
	else
		writer->writeCharsUnchecked(" NOP");
}

void CodeGeneratorVisitor::visit(NodeStatementAssign *node) {
	NodeIndex *index = node->getIndex();
	NodeIdentifier *identifier = node->getIdentifier();
	NodeExp *exp = node->getExpression();

	exp->accept(this);

	writer->writeCharsUnchecked(" LA ");
	writer->writeChars(identifier->getInformation()->getLength(), identifier->getLexem());
	
	if (index != NULL)
		index->accept(this);

	writer->writeCharsUnchecked(" STR");
}

void CodeGeneratorVisitor::visit(NodeStatementBlock *node) {
	if (node->getStatements())
		node->getStatements()->accept(this);
}

void CodeGeneratorVisitor::visit(NodeStatementIfElse *node) {
	char marke1[MAX_MARKEN_BUFFER_SIZE];
	char marke2[MAX_MARKEN_BUFFER_SIZE];

	generateJumpLabel(marke1);
	generateJumpLabel(marke2);

	node->getExpression()->accept(this);
	writer->writeCharsUnchecked(" JIN *marke"); // JIN *marke1
	writer->writeCharsUnchecked(marke1);

	node->getIfStatement()->accept(this);
	writer->writeCharsUnchecked(" JMP *marke"); // JMP *marke2
	writer->writeCharsUnchecked(marke2);
	writer->writeCharsUnchecked(" *marke"); // *marke1 NOP
	writer->writeCharsUnchecked(marke1);
	writer->writeCharsUnchecked(" NOP");

	node->getElseStatement()->accept(this);
	writer->writeCharsUnchecked(" *marke"); // *marke2 NOP
	writer->writeCharsUnchecked(marke2);
	writer->writeCharsUnchecked(" NOP");
}

void CodeGeneratorVisitor::visit(NodeStatementPrint *node) {
	node->getExpression()->accept(this);
	writer->writeCharsUnchecked(" PRI");
}

void CodeGeneratorVisitor::visit(NodeStatementRead *node) {
	NodeIndex *index = node->getIndex();
	NodeIdentifier *identifier = node->getIdentifier();

	writer->writeCharsUnchecked(" RDI");
	writer->writeCharsUnchecked(" LA ");
	writer->writeChars(identifier->getInformation()->getLength(), identifier->getLexem());

	if (index != NULL)
		index->accept(this);

	writer->writeCharsUnchecked(" STR");
}

void CodeGeneratorVisitor::visit(NodeStatementWhile *node) {
	char marke1[MAX_MARKEN_BUFFER_SIZE];
	char marke2[MAX_MARKEN_BUFFER_SIZE];

	generateJumpLabel(marke1);
	generateJumpLabel(marke2);

	writer->writeCharsUnchecked(" *marke"); // *marke1 NOP
	writer->writeCharsUnchecked(marke1);
	writer->writeCharsUnchecked(" NOP");

	node->getExpression()->accept(this);
	writer->writeCharsUnchecked(" JIN *marke"); // JIN *marke2
	writer->writeCharsUnchecked(marke2);

	node->getStatement()->accept(this);
	writer->writeCharsUnchecked(" JMP *marke"); // JMP *marke1
	writer->writeCharsUnchecked(marke1);
	writer->writeCharsUnchecked(" *marke"); // *marke2 NOP
	writer->writeCharsUnchecked(marke2);
	writer->writeCharsUnchecked(" NOP");
}

void CodeGeneratorVisitor::visit(NodeExp* node) {
	NodeOpExp *opExp = node->getOperatorExpression();

	if (opExp == NULL) {
		node->getExpression()->accept(this);
	}
	else if (opExp->getOperation()->getType() == Node::TYPE_OP_GREATER) {
		opExp->accept(this);
		node->getExpression()->accept(this);
		writer->writeCharsUnchecked(" LSI");
	}
	else if (opExp->getOperation()->getType() == Node::TYPE_OP_UNEQUAL) {
		node->getExpression()->accept(this);
		opExp->accept(this);
		writer->writeCharsUnchecked(" NOT");
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

	writer->writeCharsUnchecked(" LA ");
	writer->writeChars(identifier->getInformation()->getLength(), identifier->getLexem());

	if (index != NULL)
		index->accept(this);

	writer->writeCharsUnchecked(" LV");
}

void CodeGeneratorVisitor::visit(NodeExp2Integer* node) {
	writer->writeCharsUnchecked(" LC ");

	char temp[30];
	ltoa(node->getInteger()->getValue(), temp, 10);
	writer->writeCharsUnchecked(temp);
}

void CodeGeneratorVisitor::visit(NodeExp2NegativeExp* node) {
	writer->writeCharsUnchecked(" LC 0");
	node->getExpression()->accept(this);
	writer->writeCharsUnchecked(" SBI");
}

void CodeGeneratorVisitor::visit(NodeExp2NotExp* node) {
	node->getExpression()->accept(this);
	writer->writeCharsUnchecked(" NOT");
}


void CodeGeneratorVisitor::visit(NodeIndex* node) {
	node->getExpression()->accept(this);
	writer->writeCharsUnchecked(" ADI");
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

	writer->writeCharsUnchecked(cmd);
}

void CodeGeneratorVisitor::visit(NodeIdentifier *node) {
	throw 7;
}

void CodeGeneratorVisitor::visit(NodeInteger *node) {
	throw 42;
}
