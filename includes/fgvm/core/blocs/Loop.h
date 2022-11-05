#pragma once

#include "Bloc.h"

namespace fgvm {
	class Loop : public Statement {
	public:
		Value* condition = nullptr;
		Bloc* loop_bloc = nullptr;
		Loop(Value* condition, Bloc* if_bloc, Bloc* else_bloc);
		virtual EStatementType stmtTypeId() const override;
	};
}