/*
 * SV2ModelVisitor.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#include "SV2ModelVisitor.h"
#include "Package.h"

SV2ModelVisitor::SV2ModelVisitor() : m_model(0) {
	// TODO Auto-generated constructor stub

}

SV2ModelVisitor::~SV2ModelVisitor() {
	// TODO Auto-generated destructor stub
}

bool SV2ModelVisitor::build(Model *model, SystemVerilogParser::Source_textContext *ctx) {
	m_model = model;
	ctx->accept(this);

	return true;
}

antlrcpp::Any SV2ModelVisitor::visitClass_declaration(SystemVerilogParser::Class_declarationContext *ctx) {
	IChildItem *ret = 0;

	ctx->name->getText();

	if (ctx->class_type()) {
		// Has a base type
	}

	for (uint32_t i=0; i<ctx->interface_class_type().size(); i++) {
		// Add interfaces implemented by this class
	}

	for (uint32_t i=0; i<ctx->class_item().size(); i++) {
		// Add children
	}

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitPackage_declaration(SystemVerilogParser::Package_declarationContext *ctx) {
	IChildItem *ret = 0;
	Package *pkg = new Package(ctx->name->getText());

	for (uint32_t i=0; i<ctx->package_item().size(); i++) {
		IChildItem *it = ctx->package_item(i)->accept(this);

		if (it) {
			pkg->addChild(it);
		}
	}

	ret = pkg;
	return ret;
}
