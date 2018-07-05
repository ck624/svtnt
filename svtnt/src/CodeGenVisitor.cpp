/*
 * CodeGenVisitor.cpp
 *
 *  Created on: Jul 5, 2018
 *      Author: ballance
 */

#include "CodeGenVisitor.h"

CodeGenVisitor::CodeGenVisitor(const std::string &outdir) : m_outdir(outdir) {
	// TODO Auto-generated constructor stub

}

CodeGenVisitor::~CodeGenVisitor() {
	// TODO Auto-generated destructor stub
}

bool CodeGenVisitor::generate(Model *m) {
	m->accept(this);

	// After we're done, create the initialization code
	fprintf(stdout, "void svtnt_init() {\n");
	for (std::vector<std::string>::const_iterator it=m_packages.begin();
			it!=m_packages.end(); it++) {
		fprintf(stdout, "  svtnt_%s_init();\n", (*it).c_str());
	}
	fprintf(stdout, "}\n");

	return true;
}

void CodeGenVisitor::visit_package(Package *p) {
	m_packages.push_back(p->getName());
	fprintf(stdout, "namespace %s {\n", p->getName().c_str());

	// TODO: perform any static initializations
	fprintf(stdout, "  void svtnt_%s_init() {\n", p->getName().c_str());
	fprintf(stdout, "  }\n");
	fprintf(stdout, "}\n");

}

