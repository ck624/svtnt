/*
 * SVTNT.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */
#pragma once
#include <string>
#include <vector>

class SVTNT {
public:
	SVTNT();

	virtual ~SVTNT();

	void add_incdir(const std::string &dir);

	void add_define(const std::string &key, const std::string &val);

	bool compile(const std::vector<std::string> &files);

	bool generate(const char &outdir);

};

