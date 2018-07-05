/*
 * SVTNT.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#include "SVTNT.h"
#include "CodeGenVisitor.h"


SVTNT::SVTNT() {
	// TODO Auto-generated constructor stub

}

SVTNT::~SVTNT() {
	// TODO Auto-generated destructor stub
}

bool SVTNT::compile(const std::vector<std::string> &files) {
	// TODO:
	return false;
}

bool SVTNT::parse(std::istream &in, const std::string &path) {
	return m_compiler.parse(in, path);
}

bool SVTNT::link() {
	return m_compiler.link();
}

bool SVTNT::generate(const std::string &outdir) {
	CodeGenVisitor codegen(outdir);

	codegen.generate(m_compiler.getModel().get());

	return true;
}
