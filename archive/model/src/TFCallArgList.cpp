/*
 * TFCallArgList.cpp
 *
 *  Created on: Jul 9, 2018
 *      Author: ballance
 */

#include "TFCallArgList.h"

TFCallArgList::TFCallArgList() {

}

TFCallArgList::TFCallArgList(const std::vector<TFCallArgH> &args) : m_arguments(args) {
	// TODO Auto-generated constructor stub

}

TFCallArgList::~TFCallArgList() {
	// TODO Auto-generated destructor stub
}

void TFCallArgList::accept(IModelVisitor *v) {
	// TODO:
}

