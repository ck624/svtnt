/*
 * DataTypeString.cpp
 *
 *  Created on: Jul 11, 2018
 *      Author: ballance
 */

#include "DataTypeString.h"

DataTypeString::DataTypeString() {
	// TODO Auto-generated constructor stub

}

DataTypeString::~DataTypeString() {
	// TODO Auto-generated destructor stub
}

void DataTypeString::accept(IModelVisitor *v) {
	v->visit_data_type_string(this);
}

