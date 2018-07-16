/*
 * ExprPsHierRef.h
 *
 *  Created on: Jul 15, 2018
 *      Author: ballance
 */

#pragma once
#include "Expr.h"
#include "IChildItem.h"
#include "ExprVarElemRef.h"
#include <vector>
#include <string>

class ExprPsHierRef : public Expr {
public:
	ExprPsHierRef(
			bool 								is_hier,
			const std::vector<ExprVarElemRefH>	&path);

	virtual ~ExprPsHierRef();

	bool isHier() const { return m_is_hier; }

	const std::vector<ExprVarElemRefH> &getPath() const { return m_path; }

	void addPath(const ExprVarElemRefH &e) { m_path.push_back(e); }

	const IChildItemH getTarget() const { return m_target; }

	void setTarget(const IChildItemH &t) { m_target = t; }

	virtual void accept(IModelVisitor *v) override;


private:
	bool							m_is_hier;
	std::vector<ExprVarElemRefH>	m_path;
	IChildItemH						m_target;

};

typedef std::shared_ptr<ExprPsHierRef> ExprPsHierRefH;

