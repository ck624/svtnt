/*
 * ImportTaskFunction.cpp
 *
 *  Created on: Jul 11, 2018
 *      Author: ballance
 */

#include "ImportTaskFunction.h"

ImportTaskFunction::ImportTaskFunction(const TaskFunctionProtoH &proto)
	: m_prototype(proto), m_is_svtnt(false) {
	// TODO Auto-generated constructor stub

}

ImportTaskFunction::~ImportTaskFunction() {
	// TODO Auto-generated destructor stub
}


void ImportTaskFunction::accept(IModelVisitor *v) {
	v->visit_import_task_function(this);
}

