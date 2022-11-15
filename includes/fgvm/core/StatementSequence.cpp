#include "StatementSequence.h"
#include "Constants.h"
#include <iostream>

fgvm::StatementSequence::StatementSequence()
    : Statement()
{
}

void fgvm::StatementSequence::add(Statement* stmt)
{
    sequence.push_back(stmt);
}

void fgvm::StatementSequence::setSequence(std::vector<Statement*> sequence)
{
    this->sequence = sequence;
}

std::vector<fgvm::Statement*> fgvm::StatementSequence::getSequence() const
{
    return sequence;
}

fgvm::EStatementType fgvm::StatementSequence::stmtTypeId() const
{
    return fgvm::EStatementType::SequenceStmt;
}