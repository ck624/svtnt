/*
 * StatementBlock.h
 *
 *  Created on: Jul 7, 2018
 *      Author: ballance
 */

#ifndef MODEL_SRC_STATEMENTBLOCK_H_
#define MODEL_SRC_STATEMENTBLOCK_H_
#pragma once
#include "Statement.h"
#include "ScopeItem.h"

class StatementBlock : public Statement, public virtual ScopeItem {
public:
	StatementBlock();

	virtual ~StatementBlock();

	virtual void accept(IModelVisitor *v);
};

#endif /* MODEL_SRC_STATEMENTBLOCK_H_ */
