/*
 * TaskFunctionProto.h
 *
 *  Created on: Jul 11, 2018
 *      Author: ballance
 */

#ifndef MODEL_SRC_TASKFUNCTIONPROTO_H_
#define MODEL_SRC_TASKFUNCTIONPROTO_H_
#pragma once
#include <memory>
#include <vector>
#include "ChildItem.h"
#include "NamedItem.h"
#include "DataType.h"
#include "MethodParam.h"

class TaskFunctionProto : public ChildItem, public virtual NamedItem {
public:
	TaskFunctionProto(
			const std::string			&name,
			bool						is_func);

	virtual ~TaskFunctionProto();

	bool isFunc() const { return m_is_func; }

	const DataTypeH &getReturnType() const { return m_ret; }

	void setReturnType(const DataTypeH &ret) { m_ret = ret; }

	const std::vector<MethodParamH> &getParameters() const { return m_parameters; }

	void setParameters(const std::vector<MethodParamH> &p) { m_parameters = p; }

	bool isVariadic() const { return m_is_variadic; }

	void setIsVariadic(bool v=true) { m_is_variadic = v; }

	virtual void accept(IModelVisitor *v);

private:
	bool							m_is_func;
	bool							m_is_variadic;
	DataTypeH						m_ret;
	std::vector<MethodParamH>		m_parameters;

};

typedef std::shared_ptr<TaskFunctionProto> TaskFunctionProtoH;

#endif /* MODEL_SRC_TASKFUNCTIONPROTO_H_ */
