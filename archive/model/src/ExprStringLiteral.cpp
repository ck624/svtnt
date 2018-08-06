/*
 * ExprStringLiteral.cpp
 *
 *  Created on: Jul 18, 2018
 *      Author: ballance
 */

#include "ExprStringLiteral.h"

ExprStringLiteral::ExprStringLiteral(const std::string &val) : m_val(val) {
	// TODO Auto-generated constructor stub

}

ExprStringLiteral::~ExprStringLiteral() {
	// TODO Auto-generated destructor stub
}

void ExprStringLiteral::accept(IModelVisitor *v) {
	v->visit_expr_string_literal(this);
}

