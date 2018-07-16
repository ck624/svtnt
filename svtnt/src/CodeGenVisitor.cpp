/*
 * CodeGenVisitor.cpp
 *
 *  Created on: Jul 5, 2018
 *      Author: ballance
 */

#include "CodeGenVisitor.h"
#include <stdio.h>
#include <stdarg.h>

CodeGenVisitor::CodeGenVisitor(const std::string &outdir) :
	m_outdir(outdir), m_output(outdir) {
	m_active_out = 0;
	m_emit_host_types = false;
	// TODO Auto-generated constructor stub

}

CodeGenVisitor::~CodeGenVisitor() {
	// TODO Auto-generated destructor stub
}

bool CodeGenVisitor::generate(Model *m) {

	if (!m_output.init()) {
		return false;
	}

	m_emit_host_types = false;

	m_svtnt_h = m_output.open("svtnt.h");
	m_svtnt_cpp = m_output.open("svtnt.cpp");
	m_svtnt_mk = m_output.open("svtnt.mk");
	m_svtnt_unit_h = m_output.open("svtnt_unit.h");
	m_svtnt_unit_cpp = m_output.open("svtnt_unit.cpp");

	m_svtnt_dpi_h = m_output.open("svtnt_dpi.h");
	m_svtnt_dpi_cpp = m_output.open("svtnt_dpi.cpp");

	// TODO: header
	m_svtnt_dpi_h->println("#ifdef __cplusplus");
	m_svtnt_dpi_h->println("extern \"C\" {");
	m_svtnt_dpi_h->println("#endif /* __cplusplus */");

	m_svtnt_dpi_cpp->println("#include \"svtnt_dpi.h\"");

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

	// Close out the DPI header file
	m_svtnt_dpi_h->println("#ifdef __cplusplus");
	m_svtnt_dpi_h->println("}");
	m_svtnt_dpi_h->println("#endif /* __cplusplus */");

	m_output.close();

	return true;
}

void CodeGenVisitor::visit_data_type_integer_atom(DataTypeIntegerAtom *t) {
	if (!m_active_out) {
		error("m_active_out not set");
		return;
	}

	if (m_emit_host_types) {
		if (!t->isSigned()) {
			m_active_out->print("unsigned ");
		}
	} else {
		if (t->isSigned()) {
			m_active_out->print("Int");
		} else {
			m_active_out->print("Uint");
		}
	}

	switch (t->getAtomType()) {
		case DataTypeIntegerAtom::AtomByte:
			if (m_emit_host_types) {
				m_active_out->print("char");
			} else {
				m_active_out->print("8Var");
			}
			break;
		case DataTypeIntegerAtom::AtomInteger:
		case DataTypeIntegerAtom::AtomInt:
			if (m_emit_host_types) {
				m_active_out->print("int");
			} else {
				m_active_out->print("32Var");
			}
			break;
		case DataTypeIntegerAtom::AtomLongInt:
			if (m_emit_host_types) {
				m_active_out->print("long long");
			} else {
				m_active_out->print("64Var");
			}
			break;

		case DataTypeIntegerAtom::AtomShortInt:
			if (m_emit_host_types) {
				m_active_out->print("short");
			} else {
				m_active_out->print("16Var");
			}
			break;

		default:
			m_active_out->print("unknown_atom_type");
	}
}

void CodeGenVisitor::visit_data_type_string(DataTypeString *t) {
	if (m_emit_host_types) {
		m_active_out->print("char *");
	} else {
		// TODO: we'll need to track differences, I think
		m_active_out->print("std::string");
	}
}

void CodeGenVisitor::visit_import_task_function(ImportTaskFunction *tf) {
	std::string import_name;

	if (tf->getCIdentifier() != "") {
		import_name = tf->getCIdentifier();
	} else {
		import_name = tf->getPrototype()->getName();
	}

	// Write the prototype
	m_svtnt_dpi_h->print("%s", m_svtnt_dpi_h->indent());

	if (tf->getPrototype()->isFunc()) {
		// return type
		if (tf->getPrototype()->getReturnType().get()) {
			// Actual data type
			visit_with_output(
					tf->getPrototype()->getReturnType().get(),
					m_svtnt_dpi_h);
		} else {
			m_svtnt_dpi_h->print("void");
		}
	} else {
		// Return interrupt status
		m_svtnt_dpi_h->print("int");
	}

	m_svtnt_dpi_h->print(" %s(", import_name.c_str());

	for (uint32_t i=0; i<tf->getPrototype()->getParameters().size(); i++) {
		// Handle direction
		visit_with_output(
				tf->getPrototype()->getParameters().at(i).get(),
				m_svtnt_dpi_h);


		if (i+1 < tf->getPrototype()->getParameters().size() ||
				tf->getPrototype()->isVariadic()) {
			m_svtnt_dpi_h->print(", ");
		}
	}

	if (tf->getPrototype()->isVariadic()) {
		m_svtnt_dpi_h->print("...");
	}

	// TODO: parameters
	m_svtnt_dpi_h->print(");\n");

}

void CodeGenVisitor::visit_class(Class *c) {
	// TODO: find scope name
	std::string basename = "svtnt_" + c->getName();
	OutputH cls_h = m_output.open(basename + ".h");
	OutputH cls_cpp = m_output.open(basename + ".cpp");

	cls_h->println("namespace svtnt {");
//	cls_h->println("namespace  {"); // TODO: package namespace

	cls_h->inc_indent();
	cls_h->print("%sclass %s ", cls_h->indent(), c->getName().c_str());
	cls_h->print(" {\n");
	cls_h->inc_indent();

	// TODO: constructor

	ModelVisitorBase::visit_class(c);

	cls_h->dec_indent();
	cls_h->println("};");
	cls_h->dec_indent();
//	cls_h->println("}"); // TODO: package namespace
	cls_h->println("}"); // svtnt

	m_output.close(basename + ".h");
	m_output.close(basename + ".cpp");
}

void CodeGenVisitor::visit_method_param(MethodParam *p) {
	p->getDataType()->accept(this);
	m_active_out->print(" %s", p->getName().c_str());
}

void CodeGenVisitor::visit_package(Package *p) {
	std::string basename = "svtnt_" + p->getName();

	OutputH pkg_h = m_output.open(basename + ".h");
	OutputH pkg_cpp = m_output.open(basename + ".cpp");

	m_packages.push_back(p->getName());

	// Visit children
	ModelVisitorBase::visit_package(p);

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

std::string CodeGenVisitor::to_c_identifier(const std::string &id) {
	std::string ret;

	for (uint32_t i=0; i<id.length(); i++) {
		char c = id.at(i);
		// We'll implement any escaping later
		if (i == 0 && c == '\\') {
			continue;
		}
	}

	return ret;
}

void CodeGenVisitor::visit_with_output(IChildItem *c, const OutputH &out) {
	Output *curr_out = m_active_out;
	m_active_out = out.get();
	c->accept(this);
	m_active_out = curr_out;
}

void CodeGenVisitor::error(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	fprintf(stdout, "Error: ");
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");

	va_end(ap);
}

