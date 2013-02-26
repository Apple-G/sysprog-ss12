#include "Node.h"

#include <iostream>
using namespace std;

Node::Node() {
	//cout << "Node Base Constructor called..." << endl << "-> ";
	this->nodeType = Node::TYPE_NONE;
}

Node::~Node(void) {
	// Nur wichtig f�r erbende Klassen, sie zerst�ren ihre Nachfolger
}

void Node::addChild(Node* node) {
	std::cout << "Unable to resolve specific Node-Sub-Type... quitting" << std::endl;
//	system("pause");
//	exit(1);
}

void Node::setType(Node::TYPES newType) {
	this->nodeType = newType;
}

Node::TYPES Node::getType() {
	return this->nodeType;
}
