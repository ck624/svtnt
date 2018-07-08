/*
 * SV2ModelVisitor.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#pragma once
#include "SystemVerilogBaseVisitor.h"
#include "Model.h"

class SV2ModelVisitor : public virtual SystemVerilogBaseVisitor {
public:
	SV2ModelVisitor();

	virtual ~SV2ModelVisitor();

	virtual bool build(const ModelH &model, SystemVerilogParser::Source_textContext *ctx);

    virtual antlrcpp::Any visitClass_declaration(SystemVerilogParser::Class_declarationContext *ctx) override;

    virtual antlrcpp::Any visitPackage_declaration(SystemVerilogParser::Package_declarationContext *ctx) override;

    virtual antlrcpp::Any visitFunction_declaration(SystemVerilogParser::Function_declarationContext *ctx) override;

    virtual antlrcpp::Any visitTask_declaration(SystemVerilogParser::Task_declarationContext *ctx) override;

    virtual antlrcpp::Any visitTf_port_item(SystemVerilogParser::Tf_port_itemContext *ctx) override;

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

    antlrcpp::Any visitNull_statement(SystemVerilogParser::Null_statementContext *ctx) override;

    antlrcpp::Any visitSeq_block(SystemVerilogParser::Seq_blockContext *ctx) override;

protected:

    void enter(const char *fmt, ...);

    void leave(const char *fmt, ...);

    void todo(const char *fmt, ...);

    void error(const char *fmt, ...);

private:
    ModelH							m_model;

    std::vector<IScopeItem *>		m_scopes;

};

