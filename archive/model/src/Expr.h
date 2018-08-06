/*
 * Expr.h
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#pragma once
#include "IModelVisitor.h"
#include <memory>

class Expr {
public:
	Expr();

	virtual ~Expr();

	virtual void accept(IModelVisitor *v) = 0;
};

typedef std::shared_ptr<Expr> ExprH;
