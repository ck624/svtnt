/*
 * SVTNTCompiler.h
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#pragma once
#include <string>
#include <vector>
#include <map>
#include "Model.h"

class SVTNTCompiler {
public:
	SVTNTCompiler();

	virtual ~SVTNTCompiler();

	void add_incdir(const std::string &dir);

	void add_define(const std::string &key, const std::string &val);

    bool parse(
    		std::istream		&in,
			const std::string	&path);

    bool link();

    ModelH getModel() const { return m_model; }

private:
    ModelH								m_model;
    std::vector<std::string>			m_incdirs;
    std::map<std::string,std::string>	m_defines;

};

