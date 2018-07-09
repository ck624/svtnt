/*
 * ExprIncDec.cpp
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#include "ExprIncDec.h"

ExprIncDec::ExprIncDec(
		const ExprH			&target,
		bool				is_suffix,
		bool				is_inc) :
		m_target(target), m_is_suffix(is_suffix), m_is_inc(is_inc) {
	// TODO Auto-generated constructor stub

}

ExprIncDec::~ExprIncDec() {
	// TODO Auto-generated destructor stub
}

void ExprIncDec::accept(IModelVisitor *v) {
	// TODO:
}

