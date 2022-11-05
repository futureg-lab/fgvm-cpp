#pragma once
#include <queue>
#include "../Statement.h"
#include "../values/RetValue.h"

namespace fgvm {
	class Bloc : public Statement {
	public:
		std::string name;

		Bloc(std::string name);
		
		void setStmt(std::queue<Statement*> statements);
		std::queue<Statement*> getStmt() const;
		RetValue* getRetValue() const;
		void addStmt(Statement* stmt);
		void setRetValue(RetValue* ret_value);

		virtual EStatementType stmtTypeId() const override;
	private:
		std::queue<Statement*> statements;
		RetValue* ret_value = nullptr;
	};
}