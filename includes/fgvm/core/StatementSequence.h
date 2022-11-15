#pragma once

#include "Statement.h"

#include <vector>

namespace fgvm {
	class StatementSequence : public Statement {
	private:
		std::vector<Statement*> sequence;
	public:
		StatementSequence();
		void add(Statement* stmt);
		void setSequence(std::vector<Statement*> sequence);
		std::vector<Statement*> getSequence() const;
		EStatementType stmtTypeId() const override;
	};
}