/*
 * ExprStringLiteral.h
 *
 *  Created on: Jul 18, 2018
 *      Author: ballance
 */

#pragma once
#include <string>
#include "Expr.h"

class ExprStringLiteral : public Expr {
public:
	ExprStringLiteral(const std::string &val);

	virtual ~ExprStringLiteral();

	const std::string &getValue() const { return m_val; }

	virtual void accept(IModelVisitor *v) override;

private:
	std::string					m_val;
};

