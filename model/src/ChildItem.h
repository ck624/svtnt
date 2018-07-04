/*
 * ChildItem.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#pragma once
#include "IChildItem.h"

class ChildItem : public virtual IChildItem {
public:
	ChildItem(ItemType t);

	virtual ~ChildItem();

	virtual IScopeItem *getParent() const { return m_parent; }

	virtual ItemType getType() const { return m_type; }

private:
	ItemType				m_type;
	IScopeItem				*m_parent;

};

