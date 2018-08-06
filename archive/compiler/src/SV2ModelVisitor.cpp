/*
 * SV2ModelVisitor.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#include "SV2ModelVisitor.h"
#include "TaskFunction.h"
#include "MethodParam.h"
#include "DataTypeIntegerAtom.h"
#include "DataTypeString.h"
#include "Package.h"
#include "ChildItem.h"
#include "Statement.h"
#include "StatementBlock.h"
#include "StatementExpr.h"
#include "StatementFor.h"
#include "Expr.h"
#include "ExprIncDec.h"
#include "ExprStringLiteral.h"
#include "ExprTFCall.h"
#include "ExprVarElemRef.h"
#include "ExprVarRef.h"
#include "ExprPsHierRef.h"
#include "StatementVarDecl.h"
#include "StatementVarDeclItem.h"
#include "ImportTaskFunction.h"
#include "TaskFunction.h"
#include "TaskFunctionProto.h"
#include "TFCallArgList.h"
#include "TFCallArg.h"
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

	enter("visitClass_declaration %s", ctx->name->getText().c_str());

	ctx->name->getText();

	if (ctx->class_type()) {
		// Has a base type
		todo("support base type");
	}

	for (uint32_t i=0; i<ctx->interface_class_type().size(); i++) {
		// Add interfaces implemented by this class
		todo("support interface classes");
	}

	for (uint32_t i=0; i<ctx->class_item().size(); i++) {
		IChildItem *c = 0;

		try {
			c = ctx->class_item(i)->accept(this);
		} catch (std::bad_cast &e) {
			error("Failed to cast class item to IChildItem");
		}

		if (c) {
			// Add children
			// TODO:
		}
	}

	leave("visitClass_declaration %s", ctx->name->getText().c_str());

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitInterface_class_declaration(SystemVerilogParser::Interface_class_declarationContext *ctx) {
	IChildItem *ret = 0;
	enter("visitInterface_class_declaration");
	todo("visitInterface_class_declaration");
	leave("visitInterface_class_declaration");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitPackage_declaration(SystemVerilogParser::Package_declarationContext *ctx) {
	IChildItem *ret = 0;
	enter("visitPackage_declaration %s", ctx->name->getText().c_str());

	Package *pkg = new Package(ctx->name->getText());

	for (uint32_t i=0; i<ctx->package_item().size(); i++) {
		IChildItem *it = safe_accept<IChildItem>(ctx->package_item(i), "package item");

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
	std::vector<MethodParamH> params;
	SystemVerilogParser::Function_body_declarationContext *body = ctx->function_body_declaration();
	TaskFunctionProto *proto = new TaskFunctionProto(body->name->getText(), true);
	TaskFunction *tf = new TaskFunction(TaskFunctionProtoH(proto));

	if (body->class_scope()) {
		todo("handle class-external functions");
	}

	if (body->tf_port_list()) {
		MethodParam::Dir last_dir = MethodParam::DirIn;
		for (uint32_t i=0; i<body->tf_port_list()->tf_port_item().size(); i++) {
			IChildItem *c = 0;
			MethodParam *p = 0;
			try {
				c = body->tf_port_list()->tf_port_item(i)->accept(this);
				p = dynamic_cast<MethodParam *>(c);
				if (p->getDir() == MethodParam::DirNone) {
					p->setDir(last_dir);
				} else {
					last_dir = p->getDir();
				}
			} catch (std::bad_cast &e) {
				error("failed to cast method param to IChildItem");
			}
			params.push_back(MethodParamH(p));
		}
		for (uint32_t i=0; i<body->block_item_declaration().size(); i++) {
			IChildItem *c = 0;

			try {
				c = body->block_item_declaration(i)->accept(this);
			} catch (std::bad_cast &e) {
				error("failed to cast task body item to IChildItem");
			}

			if (c) {
				tf->addChild(IChildItemH(c));
			}
		}

		for (uint32_t i=0; i<body->function_statement_or_null().size(); i++) {
			IChildItem *c = 0;

			try {
				c = body->function_statement_or_null(i)->accept(this);
			} catch (std::bad_cast &e) {
				error("failed to cast function body item to IChildItem");
			}

			if (c) {
				tf->addChild(IChildItemH(c));
			}
		}
	} else {
		todo("handle old ANSI-style functions");
	}

	proto->setParameters(params);

	leave("visitFunction_declaration");

	ret = tf;
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitTask_declaration(SystemVerilogParser::Task_declarationContext *ctx) {
	IChildItem *ret = 0;
	std::vector<MethodParamH> params;
	SystemVerilogParser::Task_body_declarationContext *body = ctx->task_body_declaration();
	TaskFunctionProto *proto = new TaskFunctionProto(body->name->getText(), false);
	TaskFunction *tf = new TaskFunction(TaskFunctionProtoH(proto));

	enter("visitTask_declaration %s", body->name->getText().c_str());

	if (body->class_scope()) {
		todo("Handle external tasks");
	}

	// There's a formal port list
	if (body->tf_port_list()) {

		MethodParam::Dir last_dir = MethodParam::DirIn;
		for (uint32_t i=0; i<body->tf_port_list()->tf_port_item().size(); i++) {
			IChildItem *c = 0;
			MethodParam *p = 0;
			try {
				c = body->tf_port_list()->tf_port_item(i)->accept(this);
				p = dynamic_cast<MethodParam *>(c);
				if (p->getDir() == MethodParam::DirNone) {
					p->setDir(last_dir);
				} else {
					last_dir = p->getDir();
				}
			} catch (std::bad_cast &e) {
				error("failed to cast method param to IChildItem");
			}
			params.push_back(MethodParamH(p));
		}
		for (uint32_t i=0; i<body->block_item_declaration().size(); i++) {
			IChildItem *c = 0;

			try {
				c = body->block_item_declaration(i)->accept(this);
			} catch (std::bad_cast &e) {
				error("failed to cast task body item to IChildItem");
			}

			if (c) {
				tf->addChild(IChildItemH(c));
			}
		}

		for (uint32_t i=0; i<body->statement_or_null().size(); i++) {
			IChildItem *c = 0;

			try {
				c = body->statement_or_null(i)->accept(this);
			} catch (std::bad_cast &e) {
				error("failed to cast task body item to IChildItem");
			}

			if (c) {
				tf->addChild(IChildItemH(c));
			}
		}

	} else {
		todo("Handle Verilog-style tasks");
	}

	proto->setParameters(params);
	leave("visitTask_declaration");

	ret = tf;
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitTf_port_item(SystemVerilogParser::Tf_port_itemContext *ctx) {
	IChildItem *ret = 0;
	std::string name;
	MethodParam::Dir dir = MethodParam::DirNone;

	enter("visitTf_port_item");

	if (ctx->tf_port_direction()) {
		if (ctx->tf_port_direction()->port_direction()) {
			SystemVerilogParser::Port_directionContext *dir_c = ctx->tf_port_direction()->port_direction();
			if (dir_c->getText() == "input") {
				dir = MethodParam::DirIn;
			} else if (dir_c->getText() == "output") {
				dir = MethodParam::DirOut;
			} else if (dir_c->getText() == "inout") {
				dir = MethodParam::DirInOut;
			} else if (dir_c->getText() == "ref") {
				dir = MethodParam::DirRef;
			} else {
				error("Unknown port direction %s", dir_c->getText().c_str());
			}
		} else {
			dir = MethodParam::DirConstRef;
		}
	}

	if (ctx->port_identifier()) {
		name = ctx->port_identifier()->getText();
	}
	IChildItem *data_type = 0;

	try {
		data_type = ctx->data_type_or_implicit()->accept(this);
	} catch (std::bad_cast &e) {
		error("Failed to cast data-type to IChildItem");
	}

	MethodParam *p = new MethodParam(name, dir,
			DataTypeH(dynamic_cast<DataType *>(data_type)));

	leave("visitTf_port_item");
	ret = p;
	return ret;
}


antlrcpp::Any SV2ModelVisitor::visitFunction_prototype(SystemVerilogParser::Function_prototypeContext *ctx) {
	IChildItem *ret = 0;

	enter("visitFunction_prototype");

	TaskFunctionProto *proto = new TaskFunctionProto(
			ctx->function_identifier()->getText(), true);

	std::vector<MethodParamH> params;

	if (ctx->tf_port_list()) {

		MethodParam::Dir last_dir = MethodParam::DirIn;
		for (uint32_t i=0; i<ctx->tf_port_list()->tf_port_item().size(); i++) {
			MethodParam *p = 0;
			p = child_accept<MethodParam>(
					ctx->tf_port_list()->tf_port_item(i),
					"method parameter");
			if (p->getDir() == MethodParam::DirNone) {
				p->setDir(last_dir);
			} else {
				last_dir = p->getDir();
			}
			params.push_back(MethodParamH(p));
		}
	}

	if (ctx->tf_port_list()->is_variadic) {
		proto->setIsVariadic();
	}

	proto->setParameters(params);

	leave("visitFunction_prototype");

	ret = proto;
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitDpi_import_function(SystemVerilogParser::Dpi_import_functionContext *ctx) {
	IChildItem *ret = 0;

	enter("visitDpi_import_function");
	TaskFunctionProtoH proto(child_accept<TaskFunctionProto>(
			ctx->dpi_function_proto(), "dpi function prototype"));
	ImportTaskFunction *import = new ImportTaskFunction(proto);

	if (ctx->dpi_spec_string()->getText() == "SVTNT") {
		import->setIsSVTNT();
	}

	if (ctx->dpi_function_import_property()) {
		todo("handle pure/context for dpi import");
	}

	if (ctx->c_identifier()) {
		import->setCIdentifier(ctx->c_identifier()->getText());
	}

	leave("visitDpi_import_function");

	ret = import;
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitData_type_integer_vector(SystemVerilogParser::Data_type_integer_vectorContext *ctx) {
	IChildItem *ret = 0;
	enter("visitData_type_integer_vector");
	todo("visitData_type_integer_vector");
	enter("visitData_type_integer_vector");
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitData_type_integer_atom(SystemVerilogParser::Data_type_integer_atomContext *ctx) {
	IChildItem *ret = 0;
	enter("visitData_type_integer_atom");
	DataTypeIntegerAtom::AtomType at = DataTypeIntegerAtom::AtomInt;
	bool is_signed = true;

	if (ctx->integer_atom_type()->getText() == "byte") {
		at = DataTypeIntegerAtom::AtomByte;
	} else if (ctx->integer_atom_type()->getText() == "shortint") {
		at = DataTypeIntegerAtom::AtomShortInt;
	} else if (ctx->integer_atom_type()->getText() == "int") {
		at = DataTypeIntegerAtom::AtomInt;
	} else if (ctx->integer_atom_type()->getText() == "longint") {
		at = DataTypeIntegerAtom::AtomLongInt;
	} else if (ctx->integer_atom_type()->getText() == "integer") {
		at = DataTypeIntegerAtom::AtomInteger;
	} else if (ctx->integer_atom_type()->getText() == "time") {
		at = DataTypeIntegerAtom::AtomTime;
	} else {
		error("Unknown integer atom type %s", ctx->integer_atom_type()->getText().c_str());
	}

	if (ctx->signing()) {
		if (ctx->signing()->getText() == "signed") {
			is_signed = true;
		} else if (ctx->signing()->getText() == "unsigned") {
			is_signed = false;
		} else {
			error("unknown signing %s", ctx->signing()->getText().c_str());
		}
	}

	ret = new DataTypeIntegerAtom(at, is_signed);
	leave("visitData_type_integer_atom");
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitNon_integer_type(SystemVerilogParser::Non_integer_typeContext *ctx) {
	IChildItem *ret = 0;
	enter("visitNon_integer_type");
	todo("visitNon_integer_type");
	leave("visitNon_integer_type");
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitData_type_struct_union(SystemVerilogParser::Data_type_struct_unionContext *ctx) {
	IChildItem *ret = 0;
	enter("visitData_type_struct_union");
	todo("visitData_type_struct_union");
	leave("visitData_type_struct_union");
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitData_type_enum(SystemVerilogParser::Data_type_enumContext *ctx) {
	IChildItem *ret = 0;
	enter("visitData_type_enum");
	todo("visitData_type_enum");
	leave("visitData_type_enum");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitData_type_string(SystemVerilogParser::Data_type_stringContext *ctx) {
	IChildItem *ret = 0;
	enter("visitData_type_string");

	ret = new DataTypeString();

	leave("visitData_type_string");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitData_type_chandle(SystemVerilogParser::Data_type_chandleContext *ctx) {
	IChildItem *ret = 0;

	enter("visitData_type_chandle");
	todo("visitData_type_chandle");
	leave("visitData_type_chandle");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitData_type_virtual(SystemVerilogParser::Data_type_virtualContext *ctx) {
	IChildItem *ret = 0;

	enter("visitData_type_virtual");
	todo("visitData_type_virtual");
	leave("visitData_type_virtual");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitData_type_user_defined(SystemVerilogParser::Data_type_user_definedContext *ctx) {
	IChildItem *ret = 0;

	enter("visitData_type_user_defined");
	todo("visitData_type_user_defined");
	leave("visitData_type_user_defined");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitData_type_event(SystemVerilogParser::Data_type_eventContext *ctx) {
	IChildItem *ret = 0;

	enter("visitData_type_event");
	todo("visitData_type_event");
	leave("visitData_type_event");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitClass_type(SystemVerilogParser::Class_typeContext *ctx) {
	IChildItem *ret = 0;

	enter("visitClass_type");
	todo("visitClass_type");
	leave("visitClass_type");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitImplicit_data_type(SystemVerilogParser::Implicit_data_typeContext *ctx) {
	IChildItem *ret = 0;

	enter("visitImplicit_data_type");
	todo("visitImplicit_data_type");
	leave("visitImplicit_data_type");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitData_field_declaration(SystemVerilogParser::Data_field_declarationContext *ctx) {
	IChildItem *ret = 0;
	enter("visitData_field_declaration");
	todo("visitData_field_declaration");
	leave("visitData_field_declaration");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitType_declaration(SystemVerilogParser::Type_declarationContext *ctx) {
	IChildItem *ret = 0;
	enter("visitType_declaration");
	todo("visitType_declaration");
	leave("visitType_declaration");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitClass_data_property(SystemVerilogParser::Class_data_propertyContext *ctx) {
	IChildItem *ret = 0;
	enter("visitClass_data_property");
	todo("visitClass_data_property");
	leave("visitClass_data_property");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitClass_const_property(SystemVerilogParser::Class_const_propertyContext *ctx) {
	IChildItem *ret = 0;
	enter("visitClass_const_property");
	todo("visitClass_const_property");
	leave("visitClass_const_property");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitClass_method(SystemVerilogParser::Class_methodContext *ctx) {
	IChildItem *ret = 0;
	enter("visitClass_method");
	todo("visitClass_method");
	leave("visitClass_method");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitClass_constructor_prototype(SystemVerilogParser::Class_constructor_prototypeContext *ctx) {
	IChildItem *ret = 0;
	enter("visitClass_constructor_prototype");
	todo("visitClass_constructor_prototype");
	leave("visitClass_constructor_prototype");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitClass_constraint(SystemVerilogParser::Class_constraintContext *ctx) {
	IChildItem *ret = 0;
	enter("visitClass_constraint");
	todo("visitClass_constraint");
	leave("visitClass_constraint");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitStatement(SystemVerilogParser::StatementContext *ctx) {
	IChildItem *ret = 0;

	enter("visitStatement");

	try {
		ret = ctx->statement_item()->accept(this);
	} catch (std::bad_cast &e) {
		error("Failed to cast statement_item to IChildItem (%s)",
				ctx->statement_item()->getText().c_str());
	}

	if (ctx->block_identifier() && dynamic_cast<Statement *>(ret)) {
		dynamic_cast<Statement *>(ret)->setBlockIdentifier(
				ctx->block_identifier()->getText());
	}

	leave("visitStatement");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitNull_statement(SystemVerilogParser::Null_statementContext *ctx) {
	enter("visitNull_statement");
	leave("visitNull_statement");
	return static_cast<IChildItem *>(0);
}

antlrcpp::Any SV2ModelVisitor::visitSeq_block(SystemVerilogParser::Seq_blockContext *ctx) {
	IChildItem *ret = 0;

	enter("visitSeq_block");
	StatementBlock *block = new StatementBlock();
	for (uint32_t i=0; i<ctx->block_item_declaration().size(); i++) {
		IChildItem *c = 0;

		try {
			c = ctx->block_item_declaration(i)->accept(this);
		} catch (std::bad_cast &e) {
			error("Failed to cast block_item_declration to IChildItem (%s)",
					ctx->block_item_declaration(i)->getText().c_str());
		}

		if (c) {
			block->addChild(IChildItemH(c));
		}
	}

	for (uint32_t i=0; i<ctx->statement_or_null().size(); i++) {
		IChildItem *c = 0;

		try {
			c = ctx->statement_or_null(i)->accept(this);
		} catch (std::bad_cast &e) {
			error("Failed to cast statement_or_null to IChildItem (%s)",
					ctx->statement_or_null(i)->getText().c_str());
		}

		if (c) {
			block->addChild(IChildItemH(c));
		}
	}

	leave("visitSeq_block");

	ret = block;
	return ret;
}

/**
 * A subroutine_call_statement is only used in a statement context.
 * The TF elements below it are expressions
 */
antlrcpp::Any SV2ModelVisitor::visitSubroutine_call_statement(SystemVerilogParser::Subroutine_call_statementContext *ctx) {
	IChildItem *ret = 0;
	Expr *call_expr = 0;

	enter("visitSubroutine_call_statement");

	if (ctx->subroutine_call()) {
		call_expr = expr_accept(ctx->subroutine_call(), "subroutine_call");
	} else {
		call_expr = expr_accept(ctx->function_subroutine_call(), "function_subroutine_call");
	}

	ret = new StatementExpr(ExprH(call_expr));
	leave("visitSubroutine_call_statement");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitLoop_statement_for(SystemVerilogParser::Loop_statement_forContext *ctx) {
	IChildItem *ret = 0;
	std::vector<StatementH> init;
	Expr *cond = 0;
	std::vector<StatementH> step;
	Statement *stmt = 0;

	enter("visitLoop_statement_for");
	if (ctx->for_initialization()) {
		if (ctx->for_initialization()->list_of_variable_assignments()) {
			SystemVerilogParser::List_of_variable_assignmentsContext *as =
					ctx->for_initialization()->list_of_variable_assignments();
			for (uint32_t i=0; i<as->variable_assignment().size(); i++) {
				Statement *init_s = 0;

				try {
					IChildItem *c = as->variable_assignment(i)->accept(this);
					init_s = dynamic_cast<Statement *>(c);
				} catch (std::bad_cast &e) {
					error("Failed to cast variable_assignment to IChildItem");
				}

				if (init_s) {
					init.push_back(StatementH(init_s));
				}
			}
		} else {
			for (uint32_t i=0; i<ctx->for_initialization()->for_variable_declaration().size(); i++) {
				Statement *decl = 0;
				try {
					IChildItem *c = ctx->for_initialization()->for_variable_declaration(i)->accept(this);
					decl = dynamic_cast<Statement *>(c);
				} catch (std::bad_cast &e) {
					error("Failed to cast for_variable_declaration to IChildItem");
				}

				if (decl) {
					init.push_back(StatementH(decl));
				}
			}
		}
	}

	if (ctx->for_step()) {
		for (uint32_t i=0; i<ctx->for_step()->for_step_assignment().size(); i++) {
			Expr *expr = safe_accept2<Expr,Expr>(
					ctx->for_step()->for_step_assignment(i), "for expression");
			// TODO: StatementExpr
			step.push_back(StatementH(new StatementExpr(ExprH(expr))));
		}
	}

	stmt = safe_accept2<Statement,IChildItem>(ctx->statement_or_null(), "for loop statement");

	leave("visitLoop_statement_for");

	ret = new StatementFor(init, ExprH(cond), step, StatementH(stmt));
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitFor_variable_declaration(SystemVerilogParser::For_variable_declarationContext *ctx) {
	IChildItem *ret = 0;
	DataType *data_type = 0;

	enter("visitFor_variable_declaration");
	data_type = safe_accept2<DataType,IChildItem>(ctx->data_type(), "data_type");

	StatementVarDecl *decl = new StatementVarDecl(DataTypeH(data_type));

	for (uint32_t i=0; i<ctx->variable_identifier().size(); i++) {
		Expr *expr = safe_accept2<Expr>(ctx->expression(i), "variable initializer");
		StatementVarDeclItem *it = new StatementVarDeclItem(
				ctx->variable_identifier(i)->getText(), ExprH(expr));
		decl->addChild(IChildItemH(it));
	}

	leave("visitFor_variable_declaration");

	ret = decl;
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitString_literal(SystemVerilogParser::String_literalContext *ctx) {
	Expr *ret = 0;

	enter("visitString_literal");
	const std::string &str = ctx->DOUBLE_QUOTED_STRING()->getText();
	ret = new ExprStringLiteral(str.substr(1, str.length()-2));
	leave("visitString_literal");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitIntegral_number(SystemVerilogParser::Integral_numberContext *ctx) {
	Expr *ret = 0;

	enter("visitIntegral_number");
	leave("visitIntegral_number");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitPrimary_var_ref(SystemVerilogParser::Primary_var_refContext *ctx) {
	Expr *ret = 0;

	enter("visitPrimary_var_ref");
	ExprVarRef *href = 0;
	try {
		Expr *href_e = ctx->hierarchical_identifier()->accept(this);
		href = dynamic_cast<ExprVarRef *>(href_e);
	} catch (std::bad_cast &e) {
		error("Failed to cast hierarchical identifier");
	}

	if (ctx->class_qualifier() || ctx->package_scope()) {
		// Should set
		todo("support class-qualified variable ref");
	}

	// TODO: need to deal with the optional post-select

	leave("visitPrimary_var_ref");

	ret = href;
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitVariable_lvalue(SystemVerilogParser::Variable_lvalueContext *ctx) {
	Expr *ret = 0;

	enter("visitVariable_lvalue");

	if (ctx->hierarchical_variable_identifier()) {
		ret = safe_accept2<Expr>(ctx->hierarchical_variable_identifier(), "hierarchical_variable_identifier variable_lvalue");
	} else {
		todo("unhandled variable_lvalue %s", ctx->getText().c_str());
	}

	leave("visitVariable_lvalue");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitInc_or_dec_expression(SystemVerilogParser::Inc_or_dec_expressionContext *ctx) {
	Expr *ret = 0;
	enter("visitInc_or_dec_expression");
	bool is_suffix = ctx->is_suffix;
	bool is_inc = (ctx->inc_or_dec_operator()->getText() == "++");

	Expr *target = safe_accept2<Expr>(ctx->variable_lvalue(), "inc_or_dec lvalue");

	ret = new ExprIncDec(ExprH(target), is_suffix, is_inc);

	leave("visitInc_or_dec_expression");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitExpression(SystemVerilogParser::ExpressionContext *ctx) {
	Expr *ret = 0;
	Expr *lhs = 0, *rhs = 0;
	enter("visitExpression");

	if (ctx->lhs) {
		try {
			lhs = ctx->lhs->accept(this);
		} catch (std::bad_cast &e) {
			error("Expression lhs is not an Expr (%s)",
					ctx->lhs->getText().c_str());
		}
	}

	if (ctx->rhs) {
		try {
			rhs = ctx->rhs->accept(this);
		} catch (std::bad_cast &e) {
			error("Expression rhs is not an Expr (%s)",
					ctx->rhs->getText().c_str());
		}
	}

	if (ctx->exp_op() || ctx->mul_div_mod_op() || ctx->add_sub_op() ||
			ctx->shift_op() || ctx->logical_inequality_op() || ctx->eq_neq_op() ||
			ctx->binary_and_op() || ctx->binary_xor_op() || ctx->binary_or_op() ||
			ctx->logical_and_op() || ctx->logical_or_op()) {
		// Binary expression

	} else if (ctx->unary_operator()) {
	} else if (ctx->inc_or_dec_expression()) {
	} else if (ctx->operator_assignment()) {
		// paren
	} else if (ctx->tagged_union_expression()) {
	} else if (ctx->inside_expression()) {
	} else if (ctx->conditional_expression()) {
	} else if (ctx->primary()) {
		try {
			ret = ctx->primary()->accept(this);
		} catch (std::bad_cast &e) {
			error("primary is not an Expr (%s)", ctx->primary()->getText().c_str());
		}
	}

	leave("visitExpression");
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitFunction_subroutine_call(SystemVerilogParser::Function_subroutine_callContext *ctx) {
	Expr *ret = 0;
	enter("visitFunction_subroutine_call");
	todo("visitFunction_subroutine_call");
	leave("visitFunction_subroutine_call");

	return ret;
}

/**
 * A tf_call is still a legal expression element
 */
antlrcpp::Any SV2ModelVisitor::visitSystem_tf_call(SystemVerilogParser::System_tf_callContext *ctx) {
	Expr *ret = 0;
	TFCallArgList *call_args = 0;
	ExprPsHierRef *tf_ref = 0;

	enter("visitSystem_tf_call");
	if (ctx->is_type_call) {
		todo("System Tasks accepting types are not supported");
	} else {
		std::vector<ExprVarElemRefH> path;
		path.push_back(ExprVarElemRefH(new ExprVarElemRef(
				ctx->system_tf_identifier()->getText())));
		tf_ref = new ExprPsHierRef(false, path);

		if (ctx->list_of_arguments()) {
			call_args = child_accept<TFCallArgList>(
					ctx->list_of_arguments(), "List of arguments");
		} else {
			call_args = new TFCallArgList();
		}
	}

	ret = new ExprTFCall(ExprPsHierRefH(tf_ref), TFCallArgListH(call_args));

	leave("visitSystem_tf_call");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitTf_call(SystemVerilogParser::Tf_callContext *ctx) {
	Expr *ret = 0;

	enter("visitTf_call");
	ExprPsHierRef *tf_id = expr_accept<ExprPsHierRef>(
			ctx->ps_or_hierarchical_tf_identifier(),
			"tf_call identifier");
	TFCallArgList *call_args;

	if (ctx->list_of_arguments()) {
		call_args = child_accept<TFCallArgList>(
			ctx->list_of_arguments(),
			"tf_call list_of_arguments");

		for (uint32_t i=0; i<call_args->getArgs().size(); i++) {
			fprintf(stdout, "  arg[%d]=%p\n", i, call_args->getArgs().at(i).get());
		}
	} else {
		call_args = new TFCallArgList();
	}

	ret = new ExprTFCall(
			ExprPsHierRefH(tf_id),
			TFCallArgListH(call_args));

	leave("visitTf_call");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitList_of_arguments(SystemVerilogParser::List_of_argumentsContext *ctx) {
	IChildItem *ret = 0;
	std::vector<TFCallArgH> args;

	enter("visitList_of_arguments");

	if (ctx->list_of_pos_args()) {
		fprintf(stdout, "list_of_pos_args %s\n", ctx->list_of_pos_args()->getText().c_str());
		Expr *first = expr_accept(ctx->list_of_pos_args()->expression(),
				"first positional argument");
		fprintf(stdout, "first=%p\n", first);

		args.push_back(TFCallArgH(new TFCallArg(ExprH(first))));
		fprintf(stdout, "  args(0)=%p\n", args.at(0).get());
		for (uint32_t i=0; i<ctx->list_of_pos_args()->pos_arg().size(); i++) {
			SystemVerilogParser::Pos_argContext *arg =
					ctx->list_of_pos_args()->pos_arg(i);
			if (arg->expression()) {
				Expr *expr = expr_accept(arg->expression(),
						"positional argument");
				args.push_back(TFCallArgH(new TFCallArg(ExprH(expr))));
			} else {
				todo("default positional argument");
			}
		}
	} else if (ctx->list_of_pos_args_first_empty()) {
		fprintf(stdout, "list_of_pos_args_first_empty\n");
	} else if (ctx->all_name_mapped.size() > 0) {
		fprintf(stdout, "all_name_mapped\n");
	} else {
		fprintf(stdout, "Unknown!!\n");
	}

//	if (ctx->all_name_mapped.size() > 0) {
//	} else {
//		// Arguments are positional
//		if (ctx->expression()) {
//			fprintf(stdout, "first expression exists\n");
//		}
//		if (ctx->first_pos) {
//			fprintf(stdout, "visit first_pos %s\n", ctx->first_pos->getText().c_str());
//			Expr *expr = expr_accept(ctx->first_pos, "task arg");
//			args.push_back(TFCallArgH(new TFCallArg(ExprH(expr))));
//		} else {
//			fprintf(stdout, "add empty first parameter\n");
//			// Add an empty first parameter
//			args.push_back(TFCallArgH(new TFCallArg()));
//		}
//
//		// positional arguments
//		for (uint32_t i=0; i<ctx->pos_arg_list()->args.size(); i++) {
//			SystemVerilogParser::Pos_argContext *arg = ctx->pos_arg_list()->args.at(i);
//			if (arg->expression()) {
//				// Add a positional argument
//				fprintf(stdout, "visit positional argument\n");
//				Expr *expr = safe_accept<Expr>(arg->expression(), "positional arg");
//				args.push_back(TFCallArgH(new TFCallArg(ExprH(expr))));
//			} else {
//				fprintf(stdout, "add empty positional argument\n");
//				// Add an empty argument
//				args.push_back(TFCallArgH(new TFCallArg()));
//			}
//		}
//	}

	ret = new TFCallArgList(args);

	leave("visitList_of_arguments");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitHierarchical_identifier(SystemVerilogParser::Hierarchical_identifierContext *ctx) {
	Expr *ret = 0;
	std::vector<ExprVarElemRefH> path;

	enter("visitHierarchical_identifier (%s)", ctx->getText().c_str());

	for (uint32_t i=0; i<ctx->identifier().size(); i++) {
		Expr *left=0, *right=0;

		// TODO: deal with indexed expressions
		if (i<ctx->constant_bit_select().size()) {

		}

		ExprVarElemRef *ref = new ExprVarElemRef(
				ctx->identifier(i)->getText(),
				ExprH(left),
				ExprH(right));
		path.push_back(ExprVarElemRefH(ref));
	}

	leave("visitHierarchical_identifier");

	ret = new ExprPsHierRef(true, path);
	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitPs_or_hierarchical_identifier(SystemVerilogParser::Ps_or_hierarchical_identifierContext *ctx) {
	Expr *ret = 0;

	enter("visitPs_or_hierarchical_identifier");
	if (ctx->tf_identifier()) {
		// package_scope / tf_identifier
		ExprPsHierRef *ps = 0;
		if (ctx->package_scope()) {
			ps = expr_accept<ExprPsHierRef>(
				ctx->package_scope(), "package_scope");
			ps->addPath(ExprVarElemRefH(
					new ExprVarElemRef(ctx->tf_identifier()->getText(),
							ExprH(0), ExprH(0))
			));
		} else {
			std::vector<ExprVarElemRefH> path;
			path.push_back(ExprVarElemRefH(
					new ExprVarElemRef(ctx->tf_identifier()->getText(),
							ExprH(0), ExprH(0))
			));
			ps = new ExprPsHierRef(0, path);
		}
		ret = ps;
	} else {
		// plain hierarchical_identifier
		ret = ctx->hierarchical_tf_identifier()->hierarchical_identifier()->accept(this);
	}

	leave("visitPs_or_hierarchical_identifier");

	return ret;
}

antlrcpp::Any SV2ModelVisitor::visitPackage_scope(SystemVerilogParser::Package_scopeContext *ctx) {
	Expr *ret = 0;

	enter("visitPackage_scope");
	std::vector<ExprVarElemRefH> path;

	if (ctx->package_identifier()) {
		path.push_back(ExprVarElemRefH(new ExprVarElemRef(
				ctx->package_identifier()->identifier()->getText(),
				ExprH(0), ExprH(0))));
	} else {
		path.push_back(ExprVarElemRefH(new ExprVarElemRef("$unit", ExprH(0), ExprH(0))));
	}

	ret = new ExprPsHierRef(false, path);

	leave("visitPackage_scope");

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
	va_list ap;
	va_start(ap, fmt);

	fprintf(stdout, "Error: ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");

	va_end(ap);
}


