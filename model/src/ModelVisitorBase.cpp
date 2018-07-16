/*
 * ModelVisitorBase.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: ballance
 */

#include "ModelVisitorBase.h"

ModelVisitorBase::ModelVisitorBase() {
	// TODO Auto-generated constructor stub

}

ModelVisitorBase::~ModelVisitorBase() {
	// TODO Auto-generated destructor stub
}

void ModelVisitorBase::visit_class(Class *c) {
	// TODO: handle super type
	// TODO: handle interfaces
	visit_scope(c);
}

void ModelVisitorBase::visit_data_type(DataType *t) {
	// Nothing to do
}

void ModelVisitorBase::visit_data_type_integer_atom(DataTypeIntegerAtom *t) {
	// Nothing to do
}

void ModelVisitorBase::visit_data_type_string(DataTypeString *t) {
	visit_data_type(t);
}

void ModelVisitorBase::visit_expr_ps_hier_ref(ExprPsHierRef *e) {
	// If the reference has been resolved, visit it
	if (e->getTarget().get()) {
		e->getTarget().get()->accept(this);
	}
}

void ModelVisitorBase::visit_expr_tf_call(ExprTFCall *e) {
	e->getTfRef()->accept(this);
	e->getCallArgs()->accept(this);
}

void ModelVisitorBase::visit_import_task_function(ImportTaskFunction *tf) {
	tf->getPrototype()->accept(this);
}

void ModelVisitorBase::visit_method_param(MethodParam *p) {
	// TODO:
}

void ModelVisitorBase::visit_model(Model *m) {
	visit_scope(m);
}

void ModelVisitorBase::visit_package(Package *p) {
	visit_scope(p);
}

void ModelVisitorBase::visit_statement_expr(StatementExpr *s) {
	// Visit the expression
	s->getExpr()->accept(this);
}

void ModelVisitorBase::visit_task_function(TaskFunction *tf) {
	tf->getPrototype()->accept(this);
	visit_scope(tf);
}

void ModelVisitorBase::visit_scope(IScopeItem *s) {
	for (std::vector<IChildItemH>::const_iterator it=s->getChildren().begin();
			it!=s->getChildren().end(); it++) {
		(*it)->accept(this);
	}
}

