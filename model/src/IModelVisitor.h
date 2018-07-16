/*
 * IModelVisitor.h
 *
 *  Created on: Jul 4, 2018
 *      Author: ballance
 */

#pragma once

class Class;
class DataType;
class DataTypeIntegerAtom;
class DataTypeString;
class ExprPsHierRef;
class ExprTFCall;
class ImportTaskFunction;
class MethodParam;
class Model;
class Package;
class StatementExpr;
class TaskFunction;
class IModelVisitor {
public:

	virtual ~IModelVisitor() { }

	virtual void visit_class(Class *c) = 0;

	virtual void visit_data_type(DataType *t) = 0;

	virtual void visit_data_type_integer_atom(DataTypeIntegerAtom *t) = 0;

	virtual void visit_data_type_string(DataTypeString *t) = 0;

	virtual void visit_expr_ps_hier_ref(ExprPsHierRef *e) = 0;

	virtual void visit_expr_tf_call(ExprTFCall *e) = 0;

	virtual void visit_import_task_function(ImportTaskFunction *tf) = 0;

	virtual void visit_method_param(MethodParam *p) = 0;

	virtual void visit_model(Model *m) = 0;

	virtual void visit_package(Package *p) = 0;

	virtual void visit_statement_expr(StatementExpr *s) = 0;

	virtual void visit_task_function(TaskFunction *tf) = 0;
};


