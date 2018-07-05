/*
 * ModelVisitorBase.h
 *
 *  Created on: Jul 4, 2018
 *      Author: ballance
 */

#pragma once
#include "IModelVisitor.h"
#include "Model.h"
#include "Package.h"
#include "Class.h"

class ModelVisitorBase : public virtual IModelVisitor {
public:
	ModelVisitorBase();

	virtual ~ModelVisitorBase();

	virtual void visit_class(Class *c) override;

	virtual void visit_model(Model *m) override;

	virtual void visit_package(Package *p) override;

protected:

	virtual void visit_scope(IScopeItem *s);
};

