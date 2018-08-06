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
	ChildItem(ItemType t=TypeUnknown);

	virtual ~ChildItem();

	virtual void setParent(IChildItem *p) override { m_parent = p; }

	virtual IChildItem *getParent() const { return m_parent; }

	virtual ItemType getType() const { return m_type; }

private:
	ItemType				m_type;
	IChildItem				*m_parent;

};

