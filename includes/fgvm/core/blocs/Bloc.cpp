#include "Bloc.h"
#include "../utils/FGError.h"

fgvm::Bloc::Bloc(std::string name)
{
    this->name = name;
}

void fgvm::Bloc::setStmt(std::vector<Statement*> statements)
{
    this->statements = statements;
}

std::vector<fgvm::Statement*> fgvm::Bloc::getStmt() const
{
    return statements;
}

void fgvm::Bloc::addStmt(Statement* stmt)
{
    FGError::NOT_NULL(stmt);
    if (stmt->stmtTypeId() == fgvm::EStatementType::ValueStmt) {
        auto value = dynamic_cast<fgvm::Value*>(stmt);
        if (value->valueTypeID() == fgvm::EValueType::ReturnID)
            throw std::logic_error("Cannot add return object to statment list, use setRetValue instead");
    }
    statements.push_back(stmt);
}

fgvm::RetValue* fgvm::Bloc::getRetValue() const
{
    return ret_value;
}


void fgvm::Bloc::setRetValue(RetValue* ret_value)
{
    this->ret_value = ret_value;
}

fgvm::EStatementType fgvm::Bloc::stmtTypeId() const
{
    return EStatementType::BlocStmt;
}
