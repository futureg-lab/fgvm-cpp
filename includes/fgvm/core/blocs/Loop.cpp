#include "Loop.h"

fgvm::Loop::Loop(Value* condition, Bloc* if_bloc, Bloc* else_bloc)
{
	this->condition = condition;
	FGError::NOT_NULL(condition);
}

fgvm::EStatementType fgvm::Loop::stmtTypeId() const
{
	return EStatementType::LoopStmt;
}
