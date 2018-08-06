/*
 * TFCallArgList.h
 *
 *  Created on: Jul 9, 2018
 *      Author: ballance
 */

#pragma once
#include <vector>
#include <memory>
#include "ChildItem.h"
#include "TFCallArg.h"

class TFCallArgList : public ChildItem {
public:
	TFCallArgList();

	TFCallArgList(const std::vector<TFCallArgH> &args);

	virtual ~TFCallArgList();

	const std::vector<TFCallArgH> getArgs() const {
		return m_arguments;
	}

	virtual void accept(IModelVisitor *v) override;

private:

	std::vector<TFCallArgH>		m_arguments;

};

typedef std::shared_ptr<TFCallArgList> TFCallArgListH;

