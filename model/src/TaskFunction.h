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

class TaskFunction :
		public ChildItem,
		public virtual ScopeItem,
		public virtual NamedItem {
public:
	TaskFunction(
			const std::string 	&name,
			bool				is_func);

	virtual ~TaskFunction();

	bool isFunc() const { return m_is_func; }

	const DataTypeH &getReturnType() const { return m_ret; }

	void setReturnType(const DataTypeH &ret) { m_ret = ret; }

	const std::vector<MethodParamH> &getParameters() const { return m_parameters; }

	void setParameters(const std::vector<MethodParamH> &p) { m_parameters = p; }

	virtual void accept(IModelVisitor *v) override;

private:

	bool							m_is_func;
	DataTypeH						m_ret;
	std::vector<MethodParamH>		m_parameters;

};

