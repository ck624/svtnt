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

class Model : public ChildItem, public virtual ScopeItem {
public:
	Model();

	virtual ~Model();
};

typedef shptr<Model> ModelH;

