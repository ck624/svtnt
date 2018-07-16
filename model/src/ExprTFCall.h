/*
 * ExprTFCall.h
 *
 *  Created on: Jul 9, 2018
 *      Author: ballance
 */

#pragma once
#include "Expr.h"
#include "ExprPsHierRef.h"
#include "TFCallArgList.h"

class ExprTFCall : public Expr {
public:
	ExprTFCall(
			const ExprPsHierRefH 	&tf_ref,
			const TFCallArgListH	&call_args
			);

	virtual ~ExprTFCall();

	const ExprPsHierRefH &getTfRef() const { return m_tf_ref; }

	const TFCallArgListH &getCallArgs() const { return m_call_args; }

	virtual void accept(IModelVisitor *v) override;

private:
	ExprPsHierRefH				m_tf_ref;
	TFCallArgListH				m_call_args;

};

