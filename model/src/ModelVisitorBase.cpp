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

void ModelVisitorBase::visit_method_param(MethodParam *p) {
	// TODO:
}

void ModelVisitorBase::visit_model(Model *m) {
	visit_scope(m);
}

void ModelVisitorBase::visit_package(Package *p) {
	visit_scope(p);
}

void ModelVisitorBase::visit_task_function(TaskFunction *tf) {
	if (tf->isFunc() && tf->getReturnType().get()) {
		tf->getReturnType()->accept(this);
	}
}

void ModelVisitorBase::visit_scope(IScopeItem *s) {
	for (std::vector<IChildItemH>::const_iterator it=s->getChildren().begin();
			it!=s->getChildren().end(); it++) {
		(*it)->accept(this);
	}
}

