/*
 * Output.h
 *
 *  Created on: Jul 5, 2018
 *      Author: ballance
 */

#pragma once
#include <stdint.h>
#include <iostream>
#include <string>
#include <memory>

class Output {
public:
	Output(
			std::ostream 		*out,
			const std::string	&name,
			int32_t				fragment=-1);

	virtual ~Output();

	void close();

	int32_t fragment() const { return m_fragment; }

	void inc_indent();

	void dec_indent();

	void println(const char *fmt, ...);

	void print(const char *fmt, ...);

	const char *indent() const { return m_indent.c_str(); }

private:
	std::ostream				*m_out;
	std::string					m_name;
	int32_t						m_fragment;
	std::string					m_indent;
};

typedef std::shared_ptr<Output> OutputH;

