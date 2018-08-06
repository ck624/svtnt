/*
 * SVTNT.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "SVTNTCompiler.h"

class SVTNT {
public:
	SVTNT();

	virtual ~SVTNT();

	void add_incdir(const std::string &dir);

	void add_define(const std::string &key, const std::string &val);

	bool compile(const std::vector<std::string> &files);

	// Method used by compile to parse a single file
	bool parse(std::istream &in, const std::string &path);

	// Method used by compile to link types and variables
	bool link();

	bool generate(const std::string &outdir);

private:

	SVTNTCompiler			m_compiler;

};

