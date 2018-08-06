/*
 * StatementFor.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: ballance
 */

#include "StatementFor.h"

StatementFor::StatementFor(
		const std::vector<StatementH>		&init,
		const ExprH							&cond,
		const std::vector<StatementH>		&step,
		const StatementH					&stmt) :
		m_init(init), m_cond(cond), m_step(step),
		m_stmt(stmt) {
	// TODO Auto-generated constructor stub

}

StatementFor::~StatementFor() {
	// TODO Auto-generated destructor stub
}

void StatementFor::accept(IModelVisitor *v) {
	// TODO:
}

