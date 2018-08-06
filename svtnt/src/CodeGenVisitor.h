/*
 * CodeGenVisitor.h
 *
 *  Created on: Jul 5, 2018
 *      Author: ballance
 */

#ifndef SVTNT_SRC_CODEGENVISITOR_H_
#define SVTNT_SRC_CODEGENVISITOR_H_
#pragma once
#include "ModelVisitorBase.h"
#include "OutputMgr.h"
#include <string>
#include <vector>
#include <utility>

class CodeGenVisitor : public virtual ModelVisitorBase {
public:

	CodeGenVisitor(const std::string &outdir);

	virtual ~CodeGenVisitor();

	virtual bool generate(Model *m);

	virtual void visit_class(Class *c) override;

	virtual void visit_data_type_integer_atom(DataTypeIntegerAtom *t) override;

	virtual void visit_data_type_string(DataTypeString *t) override;

	virtual void visit_expr_string_literal(ExprStringLiteral *e) override;

	virtual void visit_expr_tf_call(ExprTFCall *e) override;

	virtual void visit_import_task_function(ImportTaskFunction *tf) override;

	virtual void visit_method_param(MethodParam *p) override;

	virtual void visit_package(Package *p) override;

	virtual void visit_statement_expr(StatementExpr *s) override;

	virtual void visit_task_function(TaskFunction *tf) override;


private:

	std::string to_c_identifier(const std::string &id);

	void visit_with_output(IChildItem *c, const OutputH &out);

	void error(const char *fmt, ...);

	void todo(const char *fmt, ...);

private:
	std::string					m_outdir;
	OutputMgr					m_output;
	std::vector<std::string>	m_packages;

	Output						*m_active_out;

	OutputH						m_svtnt_h;
	OutputH						m_svtnt_cpp;
	OutputH						m_svtnt_mk;
	OutputH						m_svtnt_unit_h;
	OutputH						m_svtnt_unit_cpp;

	OutputH						m_svtnt_dpi_h;
	OutputH						m_svtnt_dpi_cpp;

	std::pair<OutputH,OutputH>	m_out_file;

	// Flag controls whether types are output as SVTNT types or host types
	bool						m_emit_host_types;

};

#endif /* SVTNT_SRC_CODEGENVISITOR_H_ */
