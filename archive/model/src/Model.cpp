/*
 * Model.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#include "Model.h"

Model::Model() : ChildItem(TypeModel) {
	// TODO Auto-generated constructor stub

}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

void Model::accept(IModelVisitor *v) {
	v->visit_model(this);
}
