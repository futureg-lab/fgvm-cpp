#pragma once

#include "Value.h"
#include "../types/AtomicTypes.h"

namespace fgvm {
    // %value_name = i32 single_arg
    class RetValue : public Value {
    public:
        Value* content;
        RetValue(Value* content);
        EValueType valueTypeID() const override;
        EType expectedReductionTypeID() const override;
    };
};