#pragma once

#include <cassert>
#include <string>
#include <cassert>

namespace FGError {
	void NOT_NULL(void *value);
	void ASSERT(bool expr);
	void NOT_EMPTY(std::string str);
};