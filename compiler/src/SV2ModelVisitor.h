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

protected:

    void enter(const char *fmt, ...);

    void leave(const char *fmt, ...);

    void todo(const char *fmt, ...);

    void error(const char *fmt, ...);

private:
    ModelH							m_model;

    std::vector<IScopeItem *>		m_scopes;

};

