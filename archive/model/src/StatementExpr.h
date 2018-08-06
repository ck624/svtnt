/*
 * StatementExpr.h
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#ifndef MODEL_SRC_STATEMENTEXPR_H_
#define MODEL_SRC_STATEMENTEXPR_H_
#pragma once
#include "Statement.h"
#include "Expr.h"


class StatementExpr : public Statement {
public:
	StatementExpr(const ExprH &expr);

	virtual ~StatementExpr();

	const ExprH &getExpr() const { return m_expr; }

	virtual void accept(IModelVisitor *v) override;

private:
	ExprH					m_expr;
};

#endif /* MODEL_SRC_STATEMENTEXPR_H_ */
