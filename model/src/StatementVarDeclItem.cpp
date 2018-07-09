/*
 * StatementVarDeclItem.cpp
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#include "StatementVarDeclItem.h"

StatementVarDeclItem::StatementVarDeclItem(
		const std::string		&name,
		const ExprH				&init) : NamedItem(name), m_init(init) {
	// TODO Auto-generated constructor stub

}

StatementVarDeclItem::~StatementVarDeclItem() {
	// TODO Auto-generated destructor stub
}

void StatementVarDeclItem::accept(IModelVisitor *v) {
	// TODO:
}

