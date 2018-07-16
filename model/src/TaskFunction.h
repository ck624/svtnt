/*
 * TaskFunction.h
 *
 *  Created on: Jul 6, 2018
 *      Author: ballance
 */

#pragma once
#include "ChildItem.h"
#include "ScopeItem.h"
#include "NamedItem.h"
#include "DataType.h"
#include "MethodParam.h"
#include "TaskFunctionProto.h"

class TaskFunction :
		public ChildItem,
		public virtual ScopeItem {
public:
	TaskFunction(
			const TaskFunctionProtoH	&prototype);

	virtual ~TaskFunction();

	const TaskFunctionProtoH &getPrototype() const { return m_prototype; }

	virtual void accept(IModelVisitor *v) override;

private:
	TaskFunctionProtoH					m_prototype;


};

