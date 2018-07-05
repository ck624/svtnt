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
#include <string>
#include <vector>

class CodeGenVisitor : public virtual ModelVisitorBase {
public:

	CodeGenVisitor(const std::string &outdir);

	virtual ~CodeGenVisitor();

	virtual bool generate(Model *m);

	virtual void visit_package(Package *p) override;

private:
	std::string					m_outdir;
	std::vector<std::string>	m_packages;


};

#endif /* SVTNT_SRC_CODEGENVISITOR_H_ */
