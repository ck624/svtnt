/*
 * ImportTaskFunction.h
 *
 *  Created on: Jul 11, 2018
 *      Author: ballance
 */

#pragma once
#include "ChildItem.h"
#include "TaskFunctionProto.h"

class ImportTaskFunction : public ChildItem {

public:
	ImportTaskFunction(const TaskFunctionProtoH &prototype);

	virtual ~ImportTaskFunction();

	bool isSVNT() const { return m_is_svtnt; }

	void setIsSVTNT(bool v=true) { m_is_svtnt = v; }

	void setCIdentifier(const std::string &id) { m_c_identifier = id; }

	const std::string &getCIdentifier() const { return m_c_identifier; }

	const TaskFunctionProtoH &getPrototype() const { return m_prototype; }

	virtual void accept(IModelVisitor *v) override;

private:
	bool					m_is_svtnt;
	std::string				m_c_identifier;
	TaskFunctionProtoH		m_prototype;

};

