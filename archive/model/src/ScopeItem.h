/*
 * ScopeItem.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#pragma once
#include "IScopeItem.h"
#include <vector>


class ScopeItem : public virtual IScopeItem {
public:

	ScopeItem();

	virtual ~ScopeItem();

	virtual const std::vector<IChildItemH> &getChildren() const { return m_children; }

	virtual void addChild(const IChildItemH &c);

private:
	std::vector<IChildItemH>			m_children;
};

