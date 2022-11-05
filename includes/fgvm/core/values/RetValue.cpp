#include "RetValue.h"

fgvm::RetValue::RetValue(std::string name, fgvm::Type* content)
	: Value(name)
{
	this->content = content;
}

fgvm::EValueType fgvm::RetValue::valueTypeID() const
{
	return EValueType::ReturnID;
}

fgvm::EType fgvm::RetValue::expectedReductionTypeID() const
{
	return content->getTypeId();
}
