#pragma once
#include "../Statement.h"
#include "../values/RetValue.h"

#include <vector>

namespace fgvm {
	class Bloc : public Statement {
	public:
		std::string name;

		Bloc(std::string name);
		
		void setStmt(std::vector<Statement*> statements);
		std::vector<Statement*> getStmt() const;
		RetValue* getRetValue() const;
		void addStmt(Statement* stmt);
		void setRetValue(RetValue* ret_value);

		virtual EStatementType stmtTypeId() const override;
	private:
		std::vector<Statement*> statements;
		RetValue* ret_value = nullptr;
	};
}