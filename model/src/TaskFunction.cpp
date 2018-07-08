/*
 * TaskFunction.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: ballance
 */

#include "TaskFunction.h"

TaskFunction::TaskFunction(
		const std::string 	&name,
		bool				is_func) :
		ChildItem(TypeTaskFunc),
		NamedItem(name), m_is_func(is_func) {
	// TODO Auto-generated constructor stub

}

TaskFunction::~TaskFunction() {
	// TODO Auto-generated destructor stub
}

void TaskFunction::accept(IModelVisitor *v) {
	v->visit_task_function(this);
}
