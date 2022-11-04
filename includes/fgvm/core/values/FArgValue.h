#pragma once

#include "../types/AtomicTypes.h"
#include "Value.h"

namespace fgvm {
    class Module;

    class FArgValue : public Value {
        Type* content;
        FArgValue(std::string name, Type* content, Module* module_owner);
        EValueType valueTypeID() const override;
        EType expectedReductionTypeID() const override;
    };
}