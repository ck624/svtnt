/*
 * ExprVarRef.h
 *
 *  Created on: Jul 8, 2018
 *      Author: ballance
 */

#ifndef MODEL_SRC_EXPRVARREF_H_
#define MODEL_SRC_EXPRVARREF_H_
#include <string>
#include <memory>
#include <vector>
#include "Expr.h"
#include "IChildItem.h"
#include "ExprVarElemRef.h"

class ExprVarRef : public Expr {
public:
	ExprVarRef(
			const std::vector<ExprVarElemRefH>	&path
			);

	virtual ~ExprVarRef();

	virtual void accept(IModelVisitor *v);

	const std::vector<ExprVarElemRefH> &getPath() const { return m_path; }

private:
	std::vector<ExprVarElemRefH>		m_path;

};

typedef std::shared_ptr<ExprVarRef> ExprVarRefH;

#endif /* MODEL_SRC_EXPRVARREF_H_ */
