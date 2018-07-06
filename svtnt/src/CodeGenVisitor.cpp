/*
 * CodeGenVisitor.cpp
 *
 *  Created on: Jul 5, 2018
 *      Author: ballance
 */

#include "CodeGenVisitor.h"

CodeGenVisitor::CodeGenVisitor(const std::string &outdir) :
	m_outdir(outdir), m_output(outdir) {
	// TODO Auto-generated constructor stub

}

CodeGenVisitor::~CodeGenVisitor() {
	// TODO Auto-generated destructor stub
}

bool CodeGenVisitor::generate(Model *m) {

	if (!m_output.init()) {
		return false;
	}

	m_svtnt_h = m_output.open("svtnt.h");
	m_svtnt_cpp = m_output.open("svtnt.cpp");
	m_svtnt_mk = m_output.open("svtnt.mk");
	m_svtnt_unit_h = m_output.open("svtnt_unit.h");
	m_svtnt_unit_cpp = m_output.open("svtnt_unit.cpp");

	m_svtnt_h->println("namespace svtnt {");
	m_svtnt_h->inc_indent();

	m_svtnt_mk->println("SVTNT_OUTDIR := $(dir $(lastword $(MAKEFILE_LIST)))");
	m_svtnt_mk->println("ifneq (1,$(RULES))");
	m_svtnt_mk->println("SVTNT_SRC_FULL = $(wildcard $(SVTNT_OUTDIR)/*.cpp)");
	m_svtnt_mk->println("SVTNT_SRC = $(notdir $(SVTNT_SRC_FULL))");
	m_svtnt_mk->println("else # Rules");
	m_svtnt_mk->println("libsvtnt.o : $(SVTNT_SRC:.cpp=.o)");
	m_svtnt_mk->println("\t$(LD) -r -o $@ $(SVTNT_SRC:.cpp=.o)");
	m_svtnt_mk->println("%%.o : $(SVTNT_OUTDIR)/%%.cpp");
	m_svtnt_mk->println("\t$(Q)$(CXX) -I$(SVTNT_OUTDIR) $(CXXFLAGS) -c -o $@ $(SVTNT_OUTDIR)/$*.cpp");
	m_svtnt_mk->println("endif");

	m->accept(this);

	// Include package header files
	for (std::vector<std::string>::const_iterator it=m_packages.begin();
			it!=m_packages.end(); it++) {
		m_svtnt_cpp->println("#include \"svtnt_%s.h\"", (*it).c_str());
	}

	m_svtnt_cpp->println("namespace svtnt {");
	m_svtnt_cpp->inc_indent();

	// After we're done, create the initialization code
	m_svtnt_h->println("void init();");

	m_svtnt_cpp->println("void init() {");
	m_svtnt_cpp->inc_indent();
	for (std::vector<std::string>::const_iterator it=m_packages.begin();
			it!=m_packages.end(); it++) {
		m_svtnt_cpp->println("%s::init();", (*it).c_str());
	}
	m_svtnt_cpp->dec_indent();
	m_svtnt_cpp->println("}");

	m_svtnt_h->dec_indent();
	m_svtnt_h->println("}");
	m_svtnt_cpp->dec_indent();
	m_svtnt_cpp->println("}");

	m_output.close();

	return true;
}

void CodeGenVisitor::visit_package(Package *p) {
	std::string basename = "svtnt_" + p->getName();

	OutputH pkg_h = m_output.open(basename + ".h");
	OutputH pkg_cpp = m_output.open(basename + ".cpp");

	m_packages.push_back(p->getName());
	pkg_h->println("namespace svtnt {");
	pkg_h->println("namespace %s {", p->getName().c_str());
	pkg_h->inc_indent();

	pkg_cpp->println("namespace svtnt {");
	pkg_cpp->println("namespace %s {", p->getName().c_str());
	pkg_cpp->inc_indent();

	pkg_cpp->println("void init() {");
	pkg_cpp->inc_indent();
	// TODO: perform any static initializations
	pkg_cpp->dec_indent();
	pkg_cpp->println("}");

	pkg_cpp->dec_indent();
	pkg_cpp->println("}");
	pkg_cpp->println("}");

	pkg_h->println("void init();");

	pkg_h->dec_indent();
	pkg_h->println("}");
	pkg_h->println("}");

	m_output.close(basename + ".h");
	m_output.close(basename + ".cpp");
}

