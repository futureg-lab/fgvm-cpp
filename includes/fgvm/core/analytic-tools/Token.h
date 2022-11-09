#pragma once
#include <string>
#include "../utils/IRUtils.h"

namespace fgvm {
	struct CursorPosition {
		int pos = -1;
		int line = 1;
		int col = 0;
	};

	class Token {
	private:
		void define(int type, std::string value, CursorPosition cursor, std::string description);
	public:
		int type = -1;
		std::string value = "";
		CursorPosition cursor;
		std::string description = "";
		Token(int type, std::string value, CursorPosition cursor, std::string description);
		Token(int type, char value, CursorPosition cursor, std::string description);
		virtual std::string to_string();
	};
}