/*
 * StatementFor.h
 *
 *  Created on: Jul 7, 2018
 *      Author: ballance
 */

#ifndef MODEL_SRC_STATEMENTFOR_H_
#define MODEL_SRC_STATEMENTFOR_H_
#include <vector>
#include "Statement.h"
#include "Expr.h"

class StatementFor : public Statement {
public:

	StatementFor(
			const std::vector<StatementH>	&init,
			const ExprH						&cond,
			const std::vector<StatementH>	&step,
			const StatementH				&stmt
			);

	virtual ~StatementFor();

	const std::vector<StatementH> &getInit() const { return m_init; }

	const ExprH &getCond() const { return m_cond; }

	const std::vector<StatementH> &getStep() const { return m_step; }

	const StatementH &getStmt() const { return m_stmt; }

	virtual void accept(IModelVisitor *v);

private:
	std::vector<StatementH>		m_init;
	ExprH						m_cond;
	std::vector<StatementH>		m_step;

	StatementH					m_stmt;
};

#endif /* MODEL_SRC_STATEMENTFOR_H_ */
