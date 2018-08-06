/*
 * StatementVarDecl.cpp
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#include "StatementVarDecl.h"

StatementVarDecl::StatementVarDecl(const DataTypeH &data_type) : m_data_type(data_type) {
	// TODO Auto-generated constructor stub

}

StatementVarDecl::~StatementVarDecl() {
	// TODO Auto-generated destructor stub
}

void StatementVarDecl::accept(IModelVisitor *v) {
	// TODO:
}

