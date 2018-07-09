/*
 * StatementVarDecl.h
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#pragma once
#include "Statement.h"
#include "DataType.h"
#include "ScopeItem.h"

class StatementVarDecl : public Statement, public virtual ScopeItem {
public:
	StatementVarDecl(
			const DataTypeH		&data_type
			);

	virtual ~StatementVarDecl();

	const DataTypeH &getDataType() const { return m_data_type; }

	virtual void accept(IModelVisitor *v) override;

private:
	DataTypeH					m_data_type;


};

