/*
 * ResolveReferencesVisitor.h
 *
 *  Created on: Jul 16, 2018
 *      Author: ballance
 */

#pragma once
#include "ModelVisitorBase.h"

class ResolveReferencesVisitor : public virtual ModelVisitorBase {
public:
	ResolveReferencesVisitor();

	virtual ~ResolveReferencesVisitor();

	void resolve_refs(const ModelH &m);

	void visit_expr_ps_hier_ref(ExprPsHierRef *e) override;

};

