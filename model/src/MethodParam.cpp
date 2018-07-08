/*
 * MethodParam.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: ballance
 */

#include "MethodParam.h"

MethodParam::MethodParam(
		const std::string			&name,
		MethodParam::Dir			dir,
		const DataTypeH				&data_type) :
			ChildItem(TypeMethodParam),
			NamedItem(name),
			m_dir(dir),
			m_data_type(data_type) {
	// TODO Auto-generated constructor stub

}

MethodParam::~MethodParam() {
	// TODO Auto-generated destructor stub
}

