#pragma once
#include "Token.h"

#include <vector>

namespace fgvm {

	class Parser {
	private:
		std::vector<Token> tokens;
		size_t cursor_pos = 0;
	public:
		Parser(std::vector<Token>& tokens);
		virtual std::string compileToIntermediateCode() = 0;
		virtual Token tokenAt(size_t pos);
		virtual Token peekNextToken();
		virtual Token nextToken();
		virtual Token currentToken();
	};
}