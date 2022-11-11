#include "FArgValue.h"
#include "../utils/FGError.h"

// FArgs
fgvm::FArgValue::FArgValue(std::string name, Type* content)
	: Value(name)
{
	this->content = content;
	FGError::NOT_NULL(this->content);
}

fgvm::EValueType fgvm::FArgValue::valueTypeID() const
{
	return EValueType::FArgumentID;
}

fgvm::EType fgvm::FArgValue::expectedReductionTypeID() const
{
	return content->getTypeId();
}
