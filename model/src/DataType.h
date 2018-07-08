/*
 * DataType.h
 *
 *  Created on: Jul 6, 2018
 *      Author: ballance
 */
#pragma once
#include <memory>
#include "ChildItem.h"

class DataType : public ChildItem {
public:
	enum TypeKind {
		IntegerAtom
	};

	DataType(TypeKind kind);

	virtual ~DataType();

	TypeKind getKind() const { return m_kind; }

	void accept(IModelVisitor *v);

private:
	TypeKind			m_kind;
};

typedef std::shared_ptr<DataType> DataTypeH;

