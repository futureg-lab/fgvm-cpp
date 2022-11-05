#include "FunctionDef.h"


fgvm::FunctionDef::FunctionDef(std::string name, std::vector<FArgValue*> arguments, Bloc* bloc_def, EType ret_type)
{
	this->name = name;
	this->bloc_def = bloc_def;
	this->arguments = arguments;
	this->ret_type = ret_type;

	FGError::NOT_EMPTY(name);
	FGError::ASSERT(ret_type != EType::Unknown);
}

fgvm::EStatementType fgvm::FunctionDef::stmtTypeId() const
{
	return EStatementType::FunDefStmt;
}
