/*
 * Output.cpp
 *
 *  Created on: Jul 5, 2018
 *      Author: ballance
 */

#include "Output.h"
#include <stdio.h>
#include <stdarg.h>

Output::Output(
		std::ostream			*out,
		const std::string		&name,
		int32_t					fragment) : m_name(name), m_fragment(fragment) {
	m_out = out;

}

Output::~Output() {
	if (m_out) {
		delete m_out;
		m_out = 0;
	}
}

void Output::close() {
	if (m_out) {
		m_out->flush();
		delete m_out;
		m_out = 0;
	}
}

void Output::inc_indent() {
	m_indent += "    ";
}

void Output::dec_indent() {
	if (m_indent.length() > 4) {
		m_indent = m_indent.substr(0, m_indent.length()-4);
	} else {
		m_indent.clear();
	}
}

void Output::println(const char *fmt, ...) {
	char buf[1024];
	va_list ap;

	va_start(ap, fmt);

	(*m_out) << m_indent;
	vsprintf(buf, fmt, ap);
	(*m_out) << buf;
	(*m_out) << std::endl;

	va_end(ap);
}

void Output::print(const char *fmt, ...) {
	char buf[1024];
	va_list ap;

	va_start(ap, fmt);

	vsprintf(buf, fmt, ap);
	(*m_out) << buf;

	va_end(ap);
}


