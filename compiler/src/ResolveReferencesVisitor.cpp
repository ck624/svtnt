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

	resolve_ref(e);

	if (e->isHier()) {

	}
	fprintf(stdout, "isHier=%d\n", e->isHier());
	for (std::vector<ExprVarElemRefH>::const_iterator it=e->getPath().begin();
			it!=e->getPath().end(); it++) {
		fprintf(stdout, "  Elem: %s\n", (*it)->getId().c_str());
	}
}

void ResolveReferencesVisitor::visit_scope(IScopeItem *s) {
	fprintf(stdout, "--> visit_scope: %p\n", s);
	m_scope_stack.push_back(s);
	ModelVisitorBase::visit_scope(s);
	m_scope_stack.pop_back();
	fprintf(stdout, "<-- visit_scope: %p\n", s);
}

void ResolveReferencesVisitor::resolve_ref(ExprPsHierRef *ref) {
	fprintf(stdout, "resolve_ref: isHier=%d pathSize=%d\n",
			ref->isHier(), ref->getPath().size());
	// Need to decide whether we're searching for a static or dynamic path
	if (!ref->isHier() && ref->getPath().size() > 1) {
		// Know we have a type-based path
		std::vector<IChildItem *>::const_reverse_iterator ds = get_decl_scope_r();

		if (ds != m_scope_stack.rend()) {
			fprintf(stdout, "Found a declaration scope\n");
			IScopeItem *scope = dynamic_cast<IScopeItem *>(*ds);
			for (uint32_t i=0; i<scope->getChildren().size(); i++) {
				fprintf(stdout, "  Child %p\n", scope->getChildren().at(i).get());
			}
		} else {
			fprintf(stdout, "No declaration scopes\n");
		}

	} else if (ref->isHier()) {
		// Know we have an instance path
	} else {
		// Otherwise, we need to search both
	}
}

IChildItem *ResolveReferencesVisitor::find_type(ExprPsHierRef *ref) {
	IChildItem *ret = 0;

	if (ref->isHier()) {
		// Begin looking for variables in this scope and inheriting scopes
	} else {
		// This could be a type reference or
	}

	return ret;
}

std::vector<IChildItem *>::const_reverse_iterator ResolveReferencesVisitor::get_decl_scope_r() const {
	std::vector<IChildItem *>::const_reverse_iterator ret = m_scope_stack.rbegin();

	while (ret != m_scope_stack.rend()) {
		if (dynamic_cast<IScopeItem *>(*ret)) {
			break;
		}
		ret--;
	}

	return ret;
}
