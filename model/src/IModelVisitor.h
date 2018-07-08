/*
 * IModelVisitor.h
 *
 *  Created on: Jul 4, 2018
 *      Author: ballance
 */

#pragma once

class Class;
class DataType;
class MethodParam;
class Model;
class Package;
class TaskFunction;
class IModelVisitor {
public:

	virtual ~IModelVisitor() { }

	virtual void visit_class(Class *c) = 0;

	virtual void visit_data_type(DataType *t) = 0;

	virtual void visit_method_param(MethodParam *p) = 0;

	virtual void visit_model(Model *m) = 0;

	virtual void visit_package(Package *p) = 0;

	virtual void visit_task_function(TaskFunction *tf) = 0;
};


