#pragma once

#include <cassert>
#include <string>
#include <cassert>

#include "../Constants.h"
#include "IRUtils.h"

#include <iostream>

namespace FGError {
	void NOT_NULL(void *value);
	void ASSERT(bool expr);
	void NOT_EMPTY(std::string str);

	std::logic_error typeMismatch(std::string preambule, fgvm::EType expected, fgvm::EType received);
	std::logic_error invalidReturn(std::string preambule, fgvm::EType expected, fgvm::EType received);
	std::logic_error notAllowed(std::string what, std::string reason);
	std::logic_error notExpected(std::string reason);
};