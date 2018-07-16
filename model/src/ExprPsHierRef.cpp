/*
 * ExprPsHierRef.cpp
 *
 *  Created on: Jul 15, 2018
 *      Author: ballance
 */

#include "ExprPsHierRef.h"

ExprPsHierRef::ExprPsHierRef(
		bool								is_hier,
		const std::vector<ExprVarElemRefH>	&path) :
		m_is_hier(is_hier), m_path(path) {

}

ExprPsHierRef::~ExprPsHierRef() {
	// TODO Auto-generated destructor stub
}

void ExprPsHierRef::accept(IModelVisitor *v) {
	v->visit_expr_ps_hier_ref(this);
}

