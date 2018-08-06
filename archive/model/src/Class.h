/*
 * Class.h
 *
 *  Created on: Jul 4, 2018
 *      Author: ballance
 */

#pragma once
#include "ScopeItem.h"
#include "ChildItem.h"
#include "NamedItem.h"

class Class : public ChildItem, public virtual ScopeItem, public virtual NamedItem {
public:
	Class(const std::string &name);

	virtual ~Class();

	virtual void accept(IModelVisitor *v) override;
};

