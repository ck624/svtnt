/*
 * DataTypeIntegerAtom.cpp
 *
 *  Created on: Jul 7, 2018
 *      Author: ballance
 */

#include "DataTypeIntegerAtom.h"

DataTypeIntegerAtom::DataTypeIntegerAtom(AtomType at, bool is_signed) :
	DataType(IntegerAtom), m_atom_type(at), m_is_signed(is_signed) {

}

DataTypeIntegerAtom::~DataTypeIntegerAtom() {
	// TODO Auto-generated destructor stub
}

