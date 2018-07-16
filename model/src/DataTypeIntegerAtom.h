/*
 * DataTypeIntegerAtom.h
 *
 *  Created on: Jul 7, 2018
 *      Author: ballance
 */

#pragma once
#include "DataType.h"

class DataTypeIntegerAtom : public DataType {
public:

	enum AtomType {
		AtomByte,
		AtomShortInt,
		AtomInt,
		AtomLongInt,
		AtomInteger,
		AtomTime
	};

	DataTypeIntegerAtom(AtomType at, bool is_signed);

	virtual ~DataTypeIntegerAtom();

	DataTypeIntegerAtom::AtomType getAtomType() const { return m_atom_type; }

	bool isSigned() const { return m_is_signed; }

	virtual void accept(IModelVisitor *v) override;

private:
	AtomType				m_atom_type;
	bool					m_is_signed;
};

