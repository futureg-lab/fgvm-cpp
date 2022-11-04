#pragma once

#include "../types/AtomicTypes.h"
#include "Value.h"

namespace fgvm {
    class Module;

    // %value_name = i32 single_arg
    class SARValue : public Value {
    public:
        Type* content;
        SARValue(std::string name, Type* content, Module* module_owner);
        EValueType valueTypeID() const override;
        EType expectedReductionTypeID() const override;
    };
};