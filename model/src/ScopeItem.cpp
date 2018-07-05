/*
 * ScopeItem.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#include "ScopeItem.h"

ScopeItem::ScopeItem() {
	// TODO Auto-generated constructor stub

}

ScopeItem::~ScopeItem() {
	// TODO Auto-generated destructor stub
}

void ScopeItem::addChild(const IChildItemH &c) {
	c->setParent(dynamic_cast<IChildItem *>(this));
	m_children.push_back(c);
}

