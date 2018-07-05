/*
 * VarBase.h
 *
 *  Created on: Jul 4, 2018
 *      Author: ballance
 */

#pragma once
#include <stdint.h>

class VarBase {
public:
	VarBase();

	virtual ~VarBase();

	virtual uint32_t n_bits() const = 0;

	virtual bool is_signed() const = 0;

};

