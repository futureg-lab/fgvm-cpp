#include "FGError.h"

void FGError::NOT_NULL(void* value)
{
	assert(value != nullptr);
}

void FGError::ASSERT(bool expr)
{
	assert(expr);
}


void FGError::NOT_EMPTY(std::string str)
{
	assert(str.size() > 0);
}
