/*
 * DataTypeString.h
 *
 *  Created on: Jul 11, 2018
 *      Author: ballance
 */

#ifndef MODEL_SRC_DATATYPESTRING_H_
#define MODEL_SRC_DATATYPESTRING_H_
#include "DataType.h"

class DataTypeString : public DataType {
public:
	DataTypeString();

	virtual ~DataTypeString();

	virtual void accept(IModelVisitor *v) override;
};

#endif /* MODEL_SRC_DATATYPESTRING_H_ */
