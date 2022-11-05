#include "Bloc.h"



fgvm::Bloc::Bloc(std::string name)
{
    this->name = name;
}

void fgvm::Bloc::setStmt(std::stack<Statement*> statements)
{
    this->statements = statements;
}

std::stack<fgvm::Statement*> fgvm::Bloc::getStmt() const
{
    return statements;
}

void fgvm::Bloc::addStmt(Statement* stmt)
{
    statements.push(stmt);
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
