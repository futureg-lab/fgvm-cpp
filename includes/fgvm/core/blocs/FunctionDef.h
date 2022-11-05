#pragma once
#include <stack>
#include "../Statement.h"
#include "../values/RetValue.h"
#include "../values/FArgValue.h"

#include "Bloc.h"

namespace fgvm {
	class FunctionDef : public Statement {
	public:
		std::string name;
		std::vector<FArgValue*> arguments;

		Bloc* bloc_def;
		EType ret_type = EType::Void;
		FunctionDef(std::string name, std::vector<FArgValue*> args, Bloc* bloc_def, EType ret_type);
		virtual EStatementType stmtTypeId() const override;
	};
}