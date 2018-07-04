/*
 * IChildItem.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#pragma once
#include "shptr.h"
#include "ItemType.h"

class IScopeItem;
class IChildItem {
public:

	virtual ~IChildItem() { }

	virtual IScopeItem *getParent() const = 0;

	virtual ItemType getType() const = 0;

};

typedef shptr<IChildItem> IChildItemH;

