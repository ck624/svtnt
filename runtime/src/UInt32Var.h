/*
 * UInt32Var.h
 *
 *  Created on: Jul 4, 2018
 *      Author: ballance
 */

#pragma once
#include "VarBase.h"

class UInt32Var : public VarBase {
public:
	UInt32Var();

	virtual ~UInt32Var();

	virtual uint32_t n_bits() const override { return 32; }

	virtual bool is_signed() const override { return false; }
};

