#include "ConditionalBr.h"
#include "../utils/FGError.h"

fgvm::ConditionalBr::ConditionalBr(Value* condition, Bloc* if_bloc, Bloc* else_bloc)
{
	this->condition = condition;
	this->true_bloc = if_bloc;
	this->else_bloc = else_bloc;

	FGError::NOT_NULL(condition);

	if (condition == nullptr)
		throw FGError::notExpected("condition is null");

	if (condition->expectedReductionTypeID() != fgvm::EType::Bool) {
		auto expected = fgvm::EType::Bool;
		auto got = condition->expectedReductionTypeID();
		throw FGError::typeMismatch("invalid condition", expected, got);
	}

	FGError::NOT_NULL(if_bloc);
}

fgvm::EStatementType fgvm::ConditionalBr::stmtTypeId() const
{
	return EStatementType::IfStmt;
}
