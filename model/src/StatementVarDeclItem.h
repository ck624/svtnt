/*
 * StatementVarDeclItem.h
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#pragma once
#include <string>
#include "Statement.h"
#include "NamedItem.h"
#include "Expr.h"

class StatementVarDeclItem : public Statement, public virtual NamedItem {
public:
	StatementVarDeclItem(
			const std::string		&name,
			const ExprH				&init
			);

	virtual ~StatementVarDeclItem();

	const ExprH &getInit() const { return m_init; }

	virtual void accept(IModelVisitor *v) override;

private:
	ExprH							m_init;
};

