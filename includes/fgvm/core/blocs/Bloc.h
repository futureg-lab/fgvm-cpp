#pragma once
#include <stack>
#include "../Statement.h"
#include "../values/RetValue.h"

namespace fgvm {
	class Bloc : public Statement {
	public:
		std::string name;

		Bloc(std::string name);
		
		void setStmt(std::stack<Statement*> statements);
		std::stack<Statement*> getStmt() const;
		RetValue* getRetValue() const;
		void addStmt(Statement* stmt);
		void setRetValue(RetValue* ret_value);

		virtual EStatementType stmtTypeId() const override;
	private:
		std::stack<Statement*> statements;
		RetValue* ret_value = nullptr;
	};
}