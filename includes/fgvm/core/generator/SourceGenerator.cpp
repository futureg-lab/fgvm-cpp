#include "SourceGenerator.h"


std::string SourceGenerator::generate(fgvm::Statement* statement)
{
	std::string src = "";
	switch (statement->stmtTypeId())
	{
	case fgvm::EStatementType::ValueStmt:
		src = generate(dynamic_cast<fgvm::Value*>(statement));
		break;
	case fgvm::EStatementType::BlocStmt:
		src = generate(dynamic_cast<fgvm::Bloc*>(statement));
		break;
	case fgvm::EStatementType::IfStmt:
		src = generate(dynamic_cast<fgvm::ConditionalBr*>(statement));
		break;
	case fgvm::EStatementType::LoopStmt:
		src = generate(dynamic_cast<fgvm::Loop*>(statement));
		break;
	case fgvm::EStatementType::FunDefStmt:
		src = generate(dynamic_cast<fgvm::FunctionDef*>(statement));
		break;
	}
	if (src.empty()) {
		if (statement)
			throw FGError::notExpected("source generation is undefined for Statement type " + statement->stmtTypeId());
		else
			throw FGError::notExpected("source generation is undefined for the NULL statement");
	}
	return src;
}

std::string SourceGenerator::generate(fgvm::Value* value)
{
	std::string src = "";
	switch (value->valueTypeID())
	{
	case fgvm::EValueType::AssignementID:
		src = generate(dynamic_cast<fgvm::SARValue*>(value));
		break;
	case fgvm::EValueType::AssignRefID:
		src = generate(dynamic_cast<fgvm::SARRefValue*>(value));
		break;
	case fgvm::EValueType::FArgumentID:
		src = generate(dynamic_cast<fgvm::FArgValue*>(value));
		break;
	case fgvm::EValueType::FunctionCallID:
		src = generate(dynamic_cast<fgvm::FunctionCustomCallValue*>(value));
		break;
	case fgvm::EValueType::FunctionCustomCallID:
		src = generate(dynamic_cast<fgvm::FunctionCustomCallValue*>(value));
		break;
	case fgvm::EValueType::ReturnID:
		src = generate(dynamic_cast<fgvm::RetValue*>(value));
		break;
	case fgvm::EValueType::UnknownID:
		break;
	}

	if (src.empty()) {
		if (value)
			throw FGError::notExpected("source generation is undefined for Value type " + std::to_string(value->valueTypeID()));
		else
			throw FGError::notExpected("source generation is undefined for the NULL value");
	}
	return src;
}
