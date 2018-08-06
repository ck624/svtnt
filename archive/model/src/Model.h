/*
 * Model.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#pragma once
#include "shptr.h"
#include "ChildItem.h"
#include "ScopeItem.h"
#include "Expr.h"

class Model : public ChildItem, public virtual ScopeItem {
public:
	Model();

	virtual ~Model();

	virtual void accept(IModelVisitor *v) override;
};

typedef shptr<Model> ModelH;

