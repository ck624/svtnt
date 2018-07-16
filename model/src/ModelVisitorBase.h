/*
 * ModelVisitorBase.h
 *
 *  Created on: Jul 4, 2018
 *      Author: ballance
 */

#pragma once
#include "IModelVisitor.h"
#include "DataType.h"
#include "DataTypeIntegerAtom.h"
#include "DataTypeString.h"
#include "Expr.h"
#include "ExprPsHierRef.h"
#include "ExprTFCall.h"
#include "ImportTaskFunction.h"
#include "MethodParam.h"
#include "Model.h"
#include "Package.h"
#include "StatementExpr.h"
#include "TaskFunction.h"
#include "Class.h"

class ModelVisitorBase : public virtual IModelVisitor {
public:
	ModelVisitorBase();

	virtual ~ModelVisitorBase();

	virtual void visit_class(Class *c) override;

	virtual void visit_data_type(DataType *t) override;

	virtual void visit_data_type_integer_atom(DataTypeIntegerAtom *t) override;

	virtual void visit_data_type_string(DataTypeString *t) override;

	void visit_expr_ps_hier_ref(ExprPsHierRef *e) override;

	virtual void visit_expr_tf_call(ExprTFCall *e) override;

	virtual void visit_import_task_function(ImportTaskFunction *tf) override;

	virtual void visit_method_param(MethodParam *p) override;

	virtual void visit_model(Model *m) override;

	virtual void visit_package(Package *p) override;

	virtual void visit_statement_expr(StatementExpr *s) override;

	virtual void visit_task_function(TaskFunction *tf) override;

protected:

	virtual void visit_scope(IScopeItem *s);
};

