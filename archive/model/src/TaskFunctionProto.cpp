/*
 * TaskFunctionProto.cpp
 *
 *  Created on: Jul 11, 2018
 *      Author: ballance
 */

#include "TaskFunctionProto.h"

TaskFunctionProto::TaskFunctionProto(
		const std::string			&name,
		bool						is_func) :
		NamedItem(name), m_is_func(is_func), m_is_variadic(false) {
	// TODO Auto-generated constructor stub

}

TaskFunctionProto::~TaskFunctionProto() {
	// TODO Auto-generated destructor stub
}

void TaskFunctionProto::accept(IModelVisitor *v) {
	// TODO:
}

