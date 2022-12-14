#pragma once
#include "Token.h"

#include <string>
#include <iostream>
#include <vector>

namespace fgvm {

	class Lexer {
	private:
		char STOP_CHAR = '\0';
	protected:
		char current_char = STOP_CHAR;
		std::string source = "";
		std::string filepath = "";
		CursorPosition cursor;

		// standard string : "hello world!"
		std::string makeString();
		// [0-9]+
		std::string makeNumber();
		// [a-zA-Z0-9_]+
		std::string makeStandardExpression();
	public:
		Lexer(std::string source, std::string filepath);
		virtual std::vector<Token> tokenize();

		static bool isNum(char character);
		static bool isAlpha(char character);
		static bool isStandardExpression(char character);
		static std::logic_error tokenError(std::string reason, CursorPosition& pos, std::string filepath);

		virtual void nextChar();
		virtual char peekNextChar() const;
		virtual bool hasEnded() const;
	};
}