#pragma once

#include "Bloc.h"

namespace fgvm {
	class ConditionalBr : public Statement {
	public:
		Value* condition = nullptr;
		Bloc* true_bloc = nullptr;
		Bloc* else_bloc = nullptr;

		ConditionalBr(Value* condition, Bloc* if_bloc, Bloc* else_bloc);
		virtual EStatementType stmtTypeId() const override;
	};
}