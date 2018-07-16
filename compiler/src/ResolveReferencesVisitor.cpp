/*
 * ResolveReferencesVisitor.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: ballance
 */

#include "ResolveReferencesVisitor.h"

ResolveReferencesVisitor::ResolveReferencesVisitor() {
	// TODO Auto-generated constructor stub

}

ResolveReferencesVisitor::~ResolveReferencesVisitor() {
	// TODO Auto-generated destructor stub
}

void ResolveReferencesVisitor::resolve_refs(const ModelH &m) {
	m->accept(this);
}

void ResolveReferencesVisitor::visit_expr_ps_hier_ref(ExprPsHierRef *e) {
	fprintf(stdout, "ResolveRferencesVisitor::visit_expr_ps_hier_ref\n");
	fprintf(stdout, "isHier=%d\n", e->isHier());
	for (std::vector<ExprVarElemRefH>::const_iterator it=e->getPath().begin();
			it!=e->getPath().end(); it++) {
		fprintf(stdout, "  Elem: %s\n", (*it)->getId().c_str());
	}
}

