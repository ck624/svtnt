/*
 * TFCallArg.h
 *
 *  Created on: Jul 9, 2018
 *      Author: ballance
 */

#ifndef MODEL_SRC_TFCALLARG_H_
#define MODEL_SRC_TFCALLARG_H_
#pragma once
#include <memory>
#include "Expr.h"

class TFCallArg {
public:
	// Positional default-value
	TFCallArg();

	// Positional specified-value
	TFCallArg(const ExprH &v);

	// Name-mapped
	TFCallArg(const std::string &name, const ExprH &v);

	bool isPositional() const { return m_is_positional; }

	const ExprH &getValue() const { return m_value; }

	bool isDefault() const { return m_value.get() == 0; }

	const std::string &getName() const { return m_name; }

	virtual ~TFCallArg();

private:
	bool				m_is_positional;
	std::string			m_name;
	ExprH				m_value;


};

typedef std::shared_ptr<TFCallArg> TFCallArgH;

#endif /* MODEL_SRC_TFCALLARG_H_ */
