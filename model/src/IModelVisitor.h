/*
 * IModelVisitor.h
 *
 *  Created on: Jul 4, 2018
 *      Author: ballance
 */

#pragma once

class Package;
class Class;
class Model;
class IModelVisitor {
public:

	virtual ~IModelVisitor() { }

	virtual void visit_class(Class *c) = 0;

	virtual void visit_model(Model *m) = 0;

	virtual void visit_package(Package *p) = 0;
};


