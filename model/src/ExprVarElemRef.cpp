/*
 * ExprVarElemRef.cpp
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#include "ExprVarElemRef.h"

ExprVarElemRef::ExprVarElemRef(
		const std::string 	&id,
		const ExprH			&left,
		const ExprH			&right) : m_id(id), m_left(left), m_right(right) {
	// TODO Auto-generated constructor stub

}

ExprVarElemRef::~ExprVarElemRef() {
	// TODO Auto-generated destructor stub
}

