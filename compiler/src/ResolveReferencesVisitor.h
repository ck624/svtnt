/*
 * ResolveReferencesVisitor.h
 *
 *  Created on: Jul 16, 2018
 *      Author: ballance
 */

#pragma once
#include "ModelVisitorBase.h"
#include <vector>

class ResolveReferencesVisitor : public virtual ModelVisitorBase {
public:
	ResolveReferencesVisitor();

	virtual ~ResolveReferencesVisitor();

	void resolve_refs(const ModelH &m);

	void visit_expr_ps_hier_ref(ExprPsHierRef *e) override;

protected:
	virtual void visit_scope(IScopeItem *s) override;

private:

	virtual void resolve_ref(ExprPsHierRef *ref);

	virtual IChildItem *find_type(ExprPsHierRef *ref);

	std::vector<IChildItem *>::const_reverse_iterator get_decl_scope_r() const;

private:
	std::vector<IChildItem *>		m_scope_stack;

};

