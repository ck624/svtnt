/*
 * Statement.h
 *
 *  Created on: Jul 7, 2018
 *      Author: ballance
 */

#pragma once
#include "ChildItem.h"
#include <memory>

class Statement : public ChildItem {
public:
	Statement();

	virtual ~Statement();

	void setBlockIdentifier(const std::string &id) { m_block_id = id; }

	const std::string &getBlockIdentifier() const { return m_block_id; }

private:
	std::string				m_block_id;
};

typedef std::shared_ptr<Statement> StatementH;
