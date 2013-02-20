#include "Parser_Tree.h"
//#include "../../TypeCheck/TypeCheckVisitor.h"
//#include "../../TypeCheck/CodeGeneratorVisitor.h"

Tree::Tree(void) {
	this->root = 0;
}

Tree::~Tree(void) {
	delete this->root;
}

void Tree::dump() {
	cout << "Dump Tree" << endl;
	this->root->dump();
}

void Tree::setRoot(NodeProg* node) {
	this->root = node;
}

NodeProg* Tree::getRoot() {
	return this->root;
}

void Tree::makeCode(OutputBuffer *output) {
	//ToDo:makeCode
	//CodeGeneratorVisitor c(output);
	//root->accept(&c);
}

bool Tree::typeCheck(OutputBuffer *output) {

	// Typecheck visitor
	//ToDo: typeCheck
	//TypeCheckVisitor t(output);
	//root->accept(&t);

	//bool success = t.completedWithoutErrors();

	//return success;

	return true;
}
