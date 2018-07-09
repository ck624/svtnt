/*
 * StatementExpr.cpp
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#include "StatementExpr.h"

StatementExpr::StatementExpr(const ExprH &expr) : m_expr(expr) {
	// TODO Auto-generated constructor stub

}

StatementExpr::~StatementExpr() {
	// TODO Auto-generated destructor stub
}

void StatementExpr::accept(IModelVisitor *v) {
	// TODO:
}

