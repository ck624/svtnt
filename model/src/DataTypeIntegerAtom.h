/*
 * DataTypeIntegerAtom.h
 *
 *  Created on: Jul 7, 2018
 *      Author: ballance
 */

#ifndef MODEL_SRC_DATATYPEINTEGERATOM_H_
#define MODEL_SRC_DATATYPEINTEGERATOM_H_
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

	AtomType getAtomType() const { return m_atom_type; }

	bool isSigned() const { return m_is_signed; }

private:
	AtomType				m_atom_type;
	bool					m_is_signed;
};

#endif /* MODEL_SRC_DATATYPEINTEGERATOM_H_ */
