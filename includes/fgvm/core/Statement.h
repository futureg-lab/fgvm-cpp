#pragma once

#include "Constants.h"

namespace fgvm {
	class Statement {
	public:
		Statement();
		virtual EStatementType stmtTypeId() const = 0;
	};
}