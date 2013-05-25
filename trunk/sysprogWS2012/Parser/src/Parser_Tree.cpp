#include "Parser_Tree.h"
#include "TypeCheckVisitor.h"
#include "CodeGeneratorVisitor.h"

Tree::Tree(void) {
	this->root = 0;
}

Tree::~Tree(void) {
	delete this->root;
}


void Tree::setRoot(NodeProg* node) {
	this->root = node;
}

NodeProg* Tree::getRoot() {
	return this->root;
}

void Tree::makeCode(Buffer *output) {
	CodeGeneratorVisitor c(output);
	root->accept(&c);
}

bool Tree::typeCheck(Buffer *output) {

	// Typecheck visitor

	TypeCheckVisitor t(output);
	root->accept(&t);

	return t.completedWithoutErrors();
}
