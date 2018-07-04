/*
 * NamedItem.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#pragma once
#include <string>
#include "INamedItem.h"

class NamedItem : public virtual INamedItem {
public:
	NamedItem(const std::string &name);

	virtual ~NamedItem();

	virtual const std::string &getName() const { return m_name; }

private:

	std::string					m_name;


};

