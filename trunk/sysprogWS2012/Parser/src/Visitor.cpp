#include "Visitor.h"

Visitor::~Visitor(void) {

}

bool Visitor::completedWithoutErrors(void) {
	return this->operationsSuccessful;
}