/*
 * INamedItem.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */
#pragma once
#include <string>

class INamedItem {
public:

	virtual ~INamedItem() { }

	virtual const std::string &getName() const = 0;

};

