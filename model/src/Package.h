/*
 * Package.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#pragma once
#include <string>
#include "ChildItem.h"
#include "ScopeItem.h"
#include "NamedItem.h"

class Package :
		public ChildItem,
		public virtual ScopeItem,
		public virtual NamedItem {
public:
	Package(const std::string &name);

	virtual ~Package();

};


