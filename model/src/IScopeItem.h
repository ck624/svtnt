/*
 * IScopeItem.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#pragma once
#include <vector>
#include "shptr.h"
#include "IChildItem.h"

class IScopeItem {
public:

	virtual ~IScopeItem() { }

	virtual const std::vector<IChildItemH> &getChildren() const = 0;

	virtual void addChild(const IChildItemH &c) = 0;

};



