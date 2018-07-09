/*
 * ExprVarRef.cpp
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#include "ExprVarRef.h"

ExprVarRef::ExprVarRef(const std::vector<ExprVarElemRefH> &path) : m_path(path) {
	// TODO Auto-generated constructor stub

}

ExprVarRef::~ExprVarRef() {
	// TODO Auto-generated destructor stub
}

void ExprVarRef::accept(IModelVisitor *v) {
	// TODO:
}

