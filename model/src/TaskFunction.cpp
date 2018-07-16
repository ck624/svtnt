/*
 * TaskFunction.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: ballance
 */

#include "TaskFunction.h"

TaskFunction::TaskFunction(
		const TaskFunctionProtoH	&prototype) : m_prototype(prototype) {

}

TaskFunction::~TaskFunction() {
	// TODO Auto-generated destructor stub
}

void TaskFunction::accept(IModelVisitor *v) {
	v->visit_task_function(this);
}
