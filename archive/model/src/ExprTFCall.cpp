/*
 * ExprTFCall.cpp
 *
 *  Created on: Jul 9, 2018
 *      Author: ballance
 */

#include "ExprTFCall.h"

ExprTFCall::ExprTFCall(
		const ExprPsHierRefH		&tf_ref,
		const TFCallArgListH		&call_args
		) : m_tf_ref(tf_ref), m_call_args(call_args) {
	// TODO Auto-generated constructor stub

}

ExprTFCall::~ExprTFCall() {
	// TODO Auto-generated destructor stub
}

void ExprTFCall::accept(IModelVisitor *v) {
	v->visit_expr_tf_call(this);
}

