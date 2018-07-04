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

	virtual bool build(Model *model, SystemVerilogParser::Source_textContext *ctx);

    virtual antlrcpp::Any visitClass_declaration(SystemVerilogParser::Class_declarationContext *ctx) override;

    virtual antlrcpp::Any visitPackage_declaration(SystemVerilogParser::Package_declarationContext *ctx) override;

private:
    Model							*m_model;

    std::vector<IScopeItem *>		m_scopes;

};

