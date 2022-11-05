#pragma once

#include "../types/AtomicTypes.h"
#include "Value.h"

namespace fgvm {
    // %value_name = i32 single_arg
    class SARValue : public Value {
    public:
        Type* content;
        SARValue(std::string name, Type* content);
        EValueType valueTypeID() const override;
        EType expectedReductionTypeID() const override;
    };
};