/*
 * Class.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: ballance
 */

#include "Class.h"

Class::Class(const std::string &name) : ChildItem(TypeClass), NamedItem(name) {
	// TODO Auto-generated constructor stub

}

Class::~Class() {
	// TODO Auto-generated destructor stub
}

void Class::accept(IModelVisitor *v) {
	v->visit_class(this);
}
