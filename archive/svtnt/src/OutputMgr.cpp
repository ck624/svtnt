/*
 * OutputMgr.cpp
 *
 *  Created on: Jul 5, 2018
 *      Author: ballance
 */

#include "OutputMgr.h"
#include <fstream>

OutputMgr::OutputMgr(const std::string &outdir) : m_outdir(outdir) {
	// TODO Auto-generated constructor stub

}

OutputMgr::~OutputMgr() {
	// TODO Auto-generated destructor stub
}

bool OutputMgr::init() {
	std::string cmd = "mkdir -p ";
	cmd += m_outdir;

	return (::system(cmd.c_str()) == 0);
}

OutputH OutputMgr::open(const std::string &name, int32_t fragment) {
	std::map<std::string,std::vector<OutputH>>::iterator it;

	if ((it = m_files.find(name)) == m_files.end()) {
		m_files[name] = std::vector<OutputH>();
	}
	std::vector<OutputH> &fragments = m_files[name];

	// Create a new file and add it to the manager
	std::ofstream *out = new std::ofstream();
	if (fragment == -1) {
		out->open(m_outdir + "/" + name);
	} else {
		// Compute an appropriate temp name
		char tmp[1024];
		sprintf(tmp, "%s/%s__%d", m_outdir.c_str(), name.c_str(), fragment);
		out->open(tmp);
	}
	OutputH outh(new Output(out, name, fragment));
	fragments.push_back(outh);

	return outh;
}

bool OutputMgr::close() {
	for (std::map<std::string,std::vector<OutputH>>::iterator it=m_files.begin();
			it!=m_files.end(); it++) {
		for (std::vector<OutputH>::iterator f_it = it->second.begin();
				f_it!=it->second.end(); f_it++) {
			(*f_it)->close();
		}
	}

	return true;
}

bool OutputMgr::close(const std::string &name) {
	std::map<std::string,std::vector<OutputH>>::iterator it = m_files.find(name);

	if (it == m_files.end()) {
		return false;
	}

	if (it->second.size() > 1) {
		// Multi-file output
	} else {
		// Just close this file
		it->second.at(0)->close();
	}

	m_files.erase(it);

	return true;
}
