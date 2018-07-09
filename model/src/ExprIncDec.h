/*
 * ExprIncDec.h
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#ifndef MODEL_SRC_EXPRINCDEC_H_
#define MODEL_SRC_EXPRINCDEC_H_
#include "Expr.h"

class ExprIncDec : public Expr {
public:
	ExprIncDec(
			const ExprH		&target,
			bool 			is_suffix,
			bool 			is_inc);

	virtual ~ExprIncDec();

	virtual void accept(IModelVisitor *v) override;

private:
	ExprH					m_target;
	bool					m_is_suffix;
	bool					m_is_inc;

};

#endif /* MODEL_SRC_EXPRINCDEC_H_ */
