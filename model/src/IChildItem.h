/*
 * IChildItem.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#pragma once
#include "shptr.h"
#include "ItemType.h"
#include "IModelVisitor.h"

class IModelVisitor;
class IChildItem {
public:

	virtual ~IChildItem() { }

	virtual void setParent(IChildItem *p) = 0;

	virtual IChildItem *getParent() const = 0;

	virtual ItemType getType() const = 0;

	virtual void accept(IModelVisitor *v) = 0;

};

typedef shptr<IChildItem> IChildItemH;

