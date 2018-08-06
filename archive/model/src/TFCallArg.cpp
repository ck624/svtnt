/*
 * TFCallArg.cpp
 *
 *  Created on: Jul 9, 2018
 *      Author: ballance
 */

#include "TFCallArg.h"

TFCallArg::TFCallArg() : m_is_positional(true) { }

TFCallArg::TFCallArg(const ExprH &v) : m_is_positional(true), m_value(v) {

}

TFCallArg::TFCallArg(const std::string &name, const ExprH &v) :
		m_is_positional(false), m_name(name), m_value(v) {

}

TFCallArg::~TFCallArg() {
	// TODO Auto-generated destructor stub
}

