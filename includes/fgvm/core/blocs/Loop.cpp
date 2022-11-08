#include "Loop.h"

fgvm::Loop::Loop(Value* condition, Bloc* loop_bloc)
{
	this->condition = condition;
	
	if (condition == nullptr)
		throw FGError::notExpected("condition is null");

	if (condition->expectedReductionTypeID() != fgvm::EType::Bool) {
		auto expected = fgvm::EType::Bool;
		auto got = condition->expectedReductionTypeID();
		throw FGError::typeMismatch("invalid condition", expected, got);
	}
	this->loop_bloc = loop_bloc;
	
	FGError::NOT_NULL(loop_bloc);
}

fgvm::EStatementType fgvm::Loop::stmtTypeId() const
{
	return EStatementType::LoopStmt;
}
