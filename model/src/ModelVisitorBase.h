/*
 * ModelVisitorBase.h
 *
 *  Created on: Jul 4, 2018
 *      Author: ballance
 */

#pragma once
#include "IModelVisitor.h"
#include "MethodParam.h"
#include "Model.h"
#include "Package.h"
#include "TaskFunction.h"
#include "Class.h"

class ModelVisitorBase : public virtual IModelVisitor {
public:
	ModelVisitorBase();

	virtual ~ModelVisitorBase();

	virtual void visit_class(Class *c) override;

	virtual void visit_data_type(DataType *t) override;

	virtual void visit_method_param(MethodParam *p) override;

	virtual void visit_model(Model *m) override;

	virtual void visit_package(Package *p) override;

	virtual void visit_task_function(TaskFunction *tf) override;

protected:

	virtual void visit_scope(IScopeItem *s);
};

