/*
 * SVTNTCompiler.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: ballance
 */

#include "SVTNTCompiler.h"
#include "SV2ModelVisitor.h"
#include "SystemVerilogParser.h"
#include "SystemVerilogLexer.h"
#include "ResolveReferencesVisitor.h"

using namespace antlr4;

SVTNTCompiler::SVTNTCompiler() : m_model(new Model()) {
	// TODO Auto-generated constructor stub

}

SVTNTCompiler::~SVTNTCompiler() {
	// TODO Auto-generated destructor stub
}

bool SVTNTCompiler::parse(std::istream &in, const std::string &path) {
	SV2ModelVisitor visitor;
	ANTLRInputStream input(in);
	SystemVerilogLexer lexer(&input);

	CommonTokenStream tokens(&lexer);

	tokens.fill();
	for (uint32_t i=0; i<tokens.size(); i++) {
		Token *t = tokens.get(i);
		fprintf(stdout, "Token: %p %d %s\n", t, t->getType(), t->getText().c_str());
	}

	SystemVerilogParser parser(&tokens);

	if (parser.getNumberOfSyntaxErrors() > 0) {
		return false;
	}

	SystemVerilogParser::Source_textContext *ctx = parser.source_text();

	visitor.build(m_model, ctx);

	return true;
}

bool SVTNTCompiler::link() {
	ResolveReferencesVisitor refs_visitor;

	refs_visitor.resolve_refs(m_model);

	// TODO:
	return true;
}
