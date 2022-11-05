#include "SARRefValue.h"

fgvm::SARRefValue::SARRefValue(std::string name, Value* content)
    : Value(name)
{
    this->hold_ref = content;
    FGError::NOT_NULL(this->hold_ref);
}

fgvm::Value* fgvm::SARRefValue::derefValue() const
{
    return hold_ref;
}

fgvm::EValueType fgvm::SARRefValue::valueTypeID() const
{
    return EValueType::AssignRefID;
}

fgvm::EType fgvm::SARRefValue::expectedReductionTypeID() const
{
    return EType::Uint32;
}
