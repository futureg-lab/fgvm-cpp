#include "RetValue.h"

fgvm::RetValue::RetValue(fgvm::Value* content)
	: Value("")
{
	this->content = content;
}

fgvm::EValueType fgvm::RetValue::valueTypeID() const
{
	return EValueType::ReturnID;
}

fgvm::EType fgvm::RetValue::expectedReductionTypeID() const
{
	return content->expectedReductionTypeID();
}
