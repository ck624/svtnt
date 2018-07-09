/*
 * ExprVarElemRef.h
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#pragma once
#include <string>
#include <memory>
#include "IChildItem.h"
#include "Expr.h"

class ExprVarElemRef {
public:
	ExprVarElemRef(
			const std::string	&id,
			const ExprH			&left,
			const ExprH			&right
			);

	virtual ~ExprVarElemRef();

	const std::string &getId() const { return m_id; }

	const IChildItemH getTarget() const { return m_target; }

	void setTarget(const IChildItemH &t) { m_target = t; }

private:
	std::string						m_id;
	ExprH							m_left;
	ExprH							m_right;
	IChildItemH						m_target;

};

typedef std::shared_ptr<ExprVarElemRef> ExprVarElemRefH;

