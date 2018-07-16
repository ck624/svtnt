/*
 * SV2ModelVisitor.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#pragma once
#include "SystemVerilogBaseVisitor.h"
#include "Model.h"
#include <typeinfo>

class SV2ModelVisitor : public virtual SystemVerilogBaseVisitor {
public:
	SV2ModelVisitor();

	virtual ~SV2ModelVisitor();

	virtual bool build(const ModelH &model, SystemVerilogParser::Source_textContext *ctx);

    virtual antlrcpp::Any visitClass_declaration(SystemVerilogParser::Class_declarationContext *ctx) override;

    virtual antlrcpp::Any visitInterface_class_declaration(SystemVerilogParser::Interface_class_declarationContext *ctx) override;

    virtual antlrcpp::Any visitPackage_declaration(SystemVerilogParser::Package_declarationContext *ctx) override;

    virtual antlrcpp::Any visitFunction_declaration(SystemVerilogParser::Function_declarationContext *ctx) override;

    virtual antlrcpp::Any visitTask_declaration(SystemVerilogParser::Task_declarationContext *ctx) override;

    virtual antlrcpp::Any visitTf_port_item(SystemVerilogParser::Tf_port_itemContext *ctx) override;

    virtual antlrcpp::Any visitFunction_prototype(SystemVerilogParser::Function_prototypeContext *ctx) override;

    virtual antlrcpp::Any visitDpi_import_function(SystemVerilogParser::Dpi_import_functionContext *ctx) override;

    antlrcpp::Any visitData_type_integer_vector(SystemVerilogParser::Data_type_integer_vectorContext *ctx) override;

    antlrcpp::Any visitData_type_integer_atom(SystemVerilogParser::Data_type_integer_atomContext *ctx) override;

    antlrcpp::Any visitNon_integer_type(SystemVerilogParser::Non_integer_typeContext *ctx) override;

    antlrcpp::Any visitData_type_struct_union(SystemVerilogParser::Data_type_struct_unionContext *ctx) override;

    antlrcpp::Any visitData_type_enum(SystemVerilogParser::Data_type_enumContext *ctx) override;

    antlrcpp::Any visitData_type_string(SystemVerilogParser::Data_type_stringContext *ctx) override;

    antlrcpp::Any visitData_type_chandle(SystemVerilogParser::Data_type_chandleContext *ctx) override;

    antlrcpp::Any visitData_type_virtual(SystemVerilogParser::Data_type_virtualContext *ctx) override;

    antlrcpp::Any visitData_type_user_defined(SystemVerilogParser::Data_type_user_definedContext *ctx) override;

    antlrcpp::Any visitData_type_event(SystemVerilogParser::Data_type_eventContext *ctx) override;

    antlrcpp::Any visitClass_type(SystemVerilogParser::Class_typeContext *ctx) override;

    antlrcpp::Any visitImplicit_data_type(SystemVerilogParser::Implicit_data_typeContext *ctx) override;

    antlrcpp::Any visitData_field_declaration(SystemVerilogParser::Data_field_declarationContext *ctx) override;

    antlrcpp::Any visitType_declaration(SystemVerilogParser::Type_declarationContext *ctx) override;

    antlrcpp::Any visitClass_data_property(SystemVerilogParser::Class_data_propertyContext *ctx) override;

    antlrcpp::Any visitClass_const_property(SystemVerilogParser::Class_const_propertyContext *ctx) override;

    antlrcpp::Any visitClass_method(SystemVerilogParser::Class_methodContext *ctx) override;

    antlrcpp::Any visitClass_constructor_prototype(SystemVerilogParser::Class_constructor_prototypeContext *ctx) override;

    antlrcpp::Any visitClass_constraint(SystemVerilogParser::Class_constraintContext *ctx) override;

    antlrcpp::Any visitStatement(SystemVerilogParser::StatementContext *ctx) override;

    antlrcpp::Any visitSubroutine_call_statement(SystemVerilogParser::Subroutine_call_statementContext *ctx) override;

    antlrcpp::Any visitLoop_statement_for(SystemVerilogParser::Loop_statement_forContext *ctx) override;

    antlrcpp::Any visitFor_variable_declaration(SystemVerilogParser::For_variable_declarationContext *ctx) override;

    antlrcpp::Any visitNull_statement(SystemVerilogParser::Null_statementContext *ctx) override;

    antlrcpp::Any visitSeq_block(SystemVerilogParser::Seq_blockContext *ctx) override;

    antlrcpp::Any visitString_literal(SystemVerilogParser::String_literalContext *ctx) override;

    antlrcpp::Any visitIntegral_number(SystemVerilogParser::Integral_numberContext *ctx) override;

    antlrcpp::Any visitPrimary_var_ref(SystemVerilogParser::Primary_var_refContext *ctx) override;

    antlrcpp::Any visitVariable_lvalue(SystemVerilogParser::Variable_lvalueContext *ctx) override;

    antlrcpp::Any visitInc_or_dec_expression(SystemVerilogParser::Inc_or_dec_expressionContext *ctx) override;

    antlrcpp::Any visitExpression(SystemVerilogParser::ExpressionContext *ctx) override;

    antlrcpp::Any visitFunction_subroutine_call(SystemVerilogParser::Function_subroutine_callContext *ctx) override;

    antlrcpp::Any visitTf_call(SystemVerilogParser::Tf_callContext *ctx) override;

    antlrcpp::Any visitSystem_tf_call(SystemVerilogParser::System_tf_callContext *ctx) override;

    antlrcpp::Any visitList_of_arguments(SystemVerilogParser::List_of_argumentsContext *ctx) override;

    antlrcpp::Any visitHierarchical_identifier(SystemVerilogParser::Hierarchical_identifierContext *ctx) override;

    antlrcpp::Any visitPs_or_hierarchical_identifier(SystemVerilogParser::Ps_or_hierarchical_identifierContext *ctx) override;

    antlrcpp::Any visitPackage_scope(SystemVerilogParser::Package_scopeContext *ctx) override;

protected:

    template <class A> A *safe_accept(
    		antlr4::ParserRuleContext *c,
			const std::string &hint) {
    	A *ret = 0;
    	try {
    		ret = c->accept(this);
    	} catch (std::bad_cast &e) {
    		error("Failed to cast %s to %s (%s)",
    				hint.c_str(),
					typeid(A).name(),
					c->getText().c_str());
    	}

    	return ret;
    }

    template <class A, class B=A> A *safe_accept2(
    		antlr4::ParserRuleContext *c,
			const std::string &hint) {
    	A *ret = 0;
    	try {
    		B *it = c->accept(this);
    		ret = dynamic_cast<A *>(it);
    	} catch (std::bad_cast &e) {
    		error("Failed to cast %s to %s (%s)",
    				hint.c_str(),
					typeid(B).name(),
					c->getText().c_str());
    	}

    	return ret;
    }

    template <class A=IChildItem> A *child_accept(
    		antlr4::ParserRuleContext *c,
			const std::string &hint,
			bool				error_on_null=true) {
    	A *ret = 0;
    	IChildItem *child = 0;
    	try {
    		child = c->accept(this);
    		ret = dynamic_cast<A *>(child);
    		if (!ret && error_on_null) {
    			error("Failed to re-cast to final type");
    		}
    	} catch (std::bad_cast &e) {
    		error("Failed to cast %s to IChildItem (%s)",
    				hint.c_str(),
					c->getText().c_str());
    	}

    	return ret;
    }

    template <class A=Expr> A *expr_accept(
    		antlr4::ParserRuleContext *c,
			const std::string &hint,
			bool				error_on_null=true) {
    	A *ret = 0;
    	Expr *expr = 0;
    	try {
    		expr = c->accept(this);
    		ret = dynamic_cast<A *>(expr);
    		if (!ret && expr && error_on_null) {
    			error("Failed to re-cast to final type (%s)",
    					hint.c_str());
    		}
    	} catch (std::bad_cast &e) {
    		error("Failed to cast %s to Expr (%s)",
    				hint.c_str(),
					c->getText().c_str());
    	}

    	return ret;
    }

    void enter(const char *fmt, ...);

    void leave(const char *fmt, ...);

    void todo(const char *fmt, ...);

    void error(const char *fmt, ...);

private:
    ModelH							m_model;

    std::vector<IScopeItem *>		m_scopes;

};

