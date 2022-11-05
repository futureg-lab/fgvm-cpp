#include "ConditionalBr.h"

fgvm::ConditionalBr::ConditionalBr(Value* condition, Bloc* if_bloc, Bloc* else_bloc)
{
	this->condition = condition;
	FGError::NOT_NULL(condition);
}

fgvm::EStatementType fgvm::ConditionalBr::stmtTypeId() const
{
	return EStatementType::IfStmt;
}
