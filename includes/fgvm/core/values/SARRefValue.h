#pragma once

#include "../types/AtomicTypes.h"
#include "Value.h"

namespace fgvm {
    // %value_name = i32 single_arg
    class SARRefValue : public Value {
    private:
        Value* hold_ref = nullptr;
    public:
        SARRefValue(std::string name, Value* hold_ref);
        Value* derefValue() const;
        EValueType valueTypeID() const override;
        EType expectedReductionTypeID() const override;
    };
};