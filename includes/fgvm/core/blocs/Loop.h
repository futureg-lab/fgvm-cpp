#pragma once

#include "Bloc.h"

namespace fgvm {
	class Loop : public Statement {
	public:
		Value* condition = nullptr;
		Bloc* loop_bloc = nullptr;
		Loop(Value* condition, Bloc* loop_bloc);
		virtual EStatementType stmtTypeId() const override;
	};
}