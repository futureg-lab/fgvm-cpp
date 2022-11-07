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

std::logic_error FGError::typeMismatch(std::string preambule, fgvm::EType expected, fgvm::EType received)
{
	std::string msg = "\nincorrect type : {0}\n \"{1}\" expected, \"{2}\" received";
	std::string str_expected = IRUtils::enumTypeToStr(expected);
	std::string str_received = IRUtils::enumTypeToStr(received);
	return std::logic_error(IRUtils::format(msg, {preambule, str_expected , str_received}));
}

std::logic_error FGError::invalidReturn(std::string preambule, fgvm::EType expected, fgvm::EType received)
{
	std::string msg = "\ninvalid return type : {0}\n \"{1}\" expected, \"{2}\" received";
	std::string str_expected = IRUtils::enumTypeToStr(expected);
	std::string str_received = IRUtils::enumTypeToStr(received);
	return std::logic_error(IRUtils::format(msg, { preambule, str_expected , str_received }));
}

std::logic_error FGError::notAllowed(std::string what, std::string reason)
{
	std::string msg = "\noperation not allowed : {0}\n{1}";
	return std::logic_error(IRUtils::format(msg, { what, reason }));
}

std::logic_error FGError::notExpected(std::string reason)
{
	std::string msg = "\nnot expected : {0}\n";
	return std::logic_error(IRUtils::format(msg, { reason }));
}
