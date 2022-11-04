#include "SARValue.h"

fgvm::SARValue::SARValue(std::string name, Type* content, Module* module_owner)
    : Value(name, module_owner)
{
    this->name = name;
    this->content = content;

    FGError::NOT_EMPTY(this->name);
    FGError::NOT_NULL(this->content);
}

fgvm::EValueType fgvm::SARValue::valueTypeID() const
{
    return EValueType::AssignementID;
}

fgvm::EType fgvm::SARValue::expectedReductionTypeID() const
{
    return content->getTypeId();
}
