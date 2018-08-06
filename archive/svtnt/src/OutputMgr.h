/*
 * OutputMgr.h
 *
 *  Created on: Jul 5, 2018
 *      Author: ballance
 */

#pragma once
#include <string>
#include <vector>
#include <map>
#include "Output.h"

class OutputMgr {
public:
	OutputMgr(const std::string &outdir);

	virtual ~OutputMgr();

	bool init();

	OutputH open(const std::string &name, int32_t fragment=-1);

	bool close();

	bool close(const std::string &name);

private:
	std::string									m_outdir;
	std::map<std::string,std::vector<OutputH>>	m_files;

};

