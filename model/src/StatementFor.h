/*
 * StatementFor.h
 *
 *  Created on: Jul 7, 2018
 *      Author: ballance
 */

#ifndef MODEL_SRC_STATEMENTFOR_H_
#define MODEL_SRC_STATEMENTFOR_H_
#include "Statement.h"

class StatementFor : public Statement {
public:

	StatementFor();

	virtual ~StatementFor();

	virtual void accept(IModelVisitor *v);
};

#endif /* MODEL_SRC_STATEMENTFOR_H_ */
