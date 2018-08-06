/*
 * MethodParam.h
 *
 *  Created on: Jul 6, 2018
 *      Author: ballance
 */

#pragma once
#include "ChildItem.h"
#include "NamedItem.h"
#include "DataType.h"
#include <memory>

class MethodParam : public ChildItem, public virtual NamedItem {
public:
	enum Dir {
		DirNone,
		DirConstRef,
		DirIn,
		DirOut,
		DirInOut,
		DirRef
	};
public:

	MethodParam(
			const std::string		&name,
			MethodParam::Dir		dir,
			const DataTypeH			&data_type);

	virtual ~MethodParam();

	MethodParam::Dir getDir() const { return m_dir; }

	void setDir(MethodParam::Dir dir) { m_dir = dir; }

	const DataTypeH &getDataType() const { return m_data_type; }


	virtual void accept(IModelVisitor *v) { v->visit_method_param(this); }

private:
	Dir								m_dir;
	DataTypeH						m_data_type;

};

typedef std::shared_ptr<MethodParam> MethodParamH;
