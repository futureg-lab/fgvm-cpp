#include "Value.h"


fgvm::Value::Value(std::string name)
{
	this->name = name;
}

fgvm::EStatementType fgvm::Value::stmtTypeId() const
{
	return EStatementType::ValueStmt;
}
