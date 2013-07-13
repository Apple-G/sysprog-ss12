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
		writer->writeMessage(" NOP\n");

	// Anweisungsende
	writer->writeMessage(" STP\n");
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
		writer->writeMessage(" 1\n");
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
		writer->writeMessage(" NOP\n");
}

void CodeGeneratorVisitor::visit(NodeStatementAssign *node) {
	NodeIndex *index = node->getIndex();
	NodeIdentifier *identifier = node->getIdentifier();
	NodeExp *exp = node->getExpression();

	exp->accept(this);

	writer->writeMessage(" LA $");
	writer->writeMessage(identifier->getLexem());
	writer->writeMessage("\n");
	
	if (index != NULL)
		index->accept(this);

	writer->writeMessage(" STR\n");
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
	writer->writeMessage("\n");

	node->getIfStatement()->accept(this);
	writer->writeMessage(" JMP #label"); // JMP #label2
	writer->writeMessage(label2);
	writer->writeMessage("\n");

	writer->writeMessage(" #label"); // #label1 NOP
	writer->writeMessage(label1);
	writer->writeMessage(" NOP\n");

	node->getElseStatement()->accept(this);
	writer->writeMessage(" #label"); // #label2 NOP
	writer->writeMessage(label2);
	writer->writeMessage(" NOP\n");
}

void CodeGeneratorVisitor::visit(NodeStatementPrint *node) {
	node->getExpression()->accept(this);
	writer->writeMessage(" PRI\n");
}

void CodeGeneratorVisitor::visit(NodeStatementRead *node) {
	NodeIndex *index = node->getIndex();
	NodeIdentifier *identifier = node->getIdentifier();

	writer->writeMessage(" REA\n");
	writer->writeMessage(" LA $");
	writer->writeMessage(identifier->getLexem());
	writer->writeMessage("\n");

	if (index != NULL)
		index->accept(this);

	writer->writeMessage(" STR\n");
}

void CodeGeneratorVisitor::visit(NodeStatementWhile *node) {
	char* label1;
	char* label2;

	label1 = CharHelper::convertInt(generateJumpLabel());
	label2 = CharHelper::convertInt(generateJumpLabel());

	writer->writeMessage(" #label"); // #label1 NOP
	writer->writeMessage(label1);
	writer->writeMessage(" NOP\n");

	node->getExpression()->accept(this);
	writer->writeMessage(" JIN #label"); // JIN #label2
	writer->writeMessage(label2);
	writer->writeMessage("\n");

	node->getStatement()->accept(this);
	writer->writeMessage(" JMP #label"); // JMP #label1
	writer->writeMessage(label1);
	writer->writeMessage("\n");

	writer->writeMessage(" #label"); // #label2 NOP
	writer->writeMessage(label2);
	writer->writeMessage(" NOP\n");
}

void CodeGeneratorVisitor::visit(NodeExp* node) {
	NodeOpExp *opExp = node->getOperatorExpression();

	if (opExp == NULL) {
		node->getExpression()->accept(this);
	}
	else if (opExp->getOperation()->getType() == Node::TYPE_OP_GREATER) {
		opExp->accept(this);
		node->getExpression()->accept(this);
		writer->writeMessage(" LES\n");
	}
	else if (opExp->getOperation()->getType() == Node::TYPE_OP_UNEQUAL) {
		node->getExpression()->accept(this);
		opExp->accept(this);
		writer->writeMessage(" NOT\n");
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
	writer->writeMessage("\n");

	if (index != NULL)
		index->accept(this);

	writer->writeMessage(" LV\n");
}

void CodeGeneratorVisitor::visit(NodeExp2Integer* node) {
	writer->writeMessage(" LC ");
	writer->writeMessage(CharHelper::convertLong(node->getInteger()->getValue()));
	writer->writeMessage("\n");
}

void CodeGeneratorVisitor::visit(NodeExp2NegativeExp* node) {
	writer->writeMessage(" LC 0\n");
	node->getExpression()->accept(this);
	writer->writeMessage(" SUB\n");
}

void CodeGeneratorVisitor::visit(NodeExp2NotExp* node) {
	node->getExpression()->accept(this);
	writer->writeMessage(" NOT\n");
}


void CodeGeneratorVisitor::visit(NodeIndex* node) {
	node->getExpression()->accept(this);
	writer->writeMessage(" ADD\n");
}

void CodeGeneratorVisitor::visit(NodeOpExp* node) {
	node->getExpression()->accept(this);
	node->getOperation()->accept(this);
}

void CodeGeneratorVisitor::visit(NodeOp* node) {
	char *cmd;

	switch (node->getType())
	{
	case Node::TYPE_OP_PLUS:     cmd = " ADD\n"; break;
	case Node::TYPE_OP_MINUS:    cmd = " SUB\n"; break;
	case Node::TYPE_OP_MULTIPLY: cmd = " MUL\n"; break;
	case Node::TYPE_OP_DIVIDE:   cmd = " DIV\n"; break;
	case Node::TYPE_OP_SMALLER:  cmd = " LES\n"; break;
	case Node::TYPE_OP_GREATER:  cmd = "\n"; break; // Bereits aufgeloest in CodeGeneratorVisitor::visit(NodeExp* node)
	case Node::TYPE_OP_EQUAL:    cmd = " EQU\n"; break;
	case Node::TYPE_OP_UNEQUAL:  cmd = " EQU\n"; break;// Bereits teilaufgeloest in CodeGeneratorVisitor::visit(NodeExp* node)
	case Node::TYPE_OP_AND:      cmd = " AND\n"; break;
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
