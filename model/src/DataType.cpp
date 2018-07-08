/*
 * DataType.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: ballance
 */

#include "DataType.h"

DataType::DataType(TypeKind kind) : ChildItem(TypeDataType), m_kind(kind) {
	// TODO Auto-generated constructor stub

}

DataType::~DataType() {
	// TODO Auto-generated destructor stub
}

void DataType::accept(IModelVisitor *v) {
	v->visit_data_type(this);
}

