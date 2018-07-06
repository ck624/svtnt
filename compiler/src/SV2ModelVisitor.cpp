/*
 * SV2ModelVisitor.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#include "SV2ModelVisitor.h"
#include "Package.h"
#include <stdio.h>

SV2ModelVisitor::SV2ModelVisitor() : m_model(0) {
	// TODO Auto-generated constructor stub

}

SV2ModelVisitor::~SV2ModelVisitor() {
	// TODO Auto-generated destructor stub
}

bool SV2ModelVisitor::build(const ModelH &model, SystemVerilogParser::Source_textContext *ctx) {
	m_model = model;

	// TODO: timeunits_declaration

	for (uint32_t i=0; i<ctx->description().size(); i++) {
		IChildItem *it = ctx->description(i)->accept(this);

		if (it) {
			model->addChild(IChildItemH(it));
		}
	}

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
	enter("visitPackage_declaration %s", ctx->name->getText().c_str());

	Package *pkg = new Package(ctx->name->getText());

	for (uint32_t i=0; i<ctx->package_item().size(); i++) {
		IChildItem *it = 0;

		try {
			it = ctx->package_item(i)->accept(this);
		} catch (std::bad_cast &e) {
			error("Failed to cast package item to IChildItem");
		}

		if (it) {
			pkg->addChild(IChildItemH(it));
		}
	}

	leave("visitPackage_declaration %s", ctx->name->getText().c_str());
	ret = pkg;
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitFunction_declaration(SystemVerilogParser::Function_declarationContext *ctx) {
	IChildItem *ret = 0;
	enter("visitFunction_declaration");
	todo("visitFunction_declaration");
	leave("visitFunction_declaration");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitTask_declaration(SystemVerilogParser::Task_declarationContext *ctx) {
	IChildItem *ret = 0;

	enter("visitTask_declaration");
	todo("visitTask_declaration");
	leave("visitTask_declaration");

	return ret;
}

void SV2ModelVisitor::enter(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	fprintf(stdout, "--> ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");

	va_end(ap);
}

void SV2ModelVisitor::leave(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	fprintf(stdout, "<-- ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");

	va_end(ap);
}

void SV2ModelVisitor::todo(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	fprintf(stdout, "TODO: ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");

	va_end(ap);
}

void SV2ModelVisitor::error(const char *fmt, ...) {

}


