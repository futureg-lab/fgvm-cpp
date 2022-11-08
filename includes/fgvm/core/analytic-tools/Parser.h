#pragma once

#include "Token.h"

namespace fgvm {
	class Parser {
	private:
		std::vector<Token> tokens;
		size_t cursor_pos = 0;
	public:
		Parser(std::vector<Token>& tokens);
		virtual std::string compileToIntermediateCode() = 0;
	protected:
		Token tokenAt(size_t pos);
		Token peekNextToken();
		Token nextToken();
		Token currentToken();
	};
}