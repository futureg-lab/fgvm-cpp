#pragma once

#include "../types/AtomicTypes.h"
#include "Value.h"

namespace fgvm {
    class FArgValue : public Value {
    public:
        Type* content;
        FArgValue(std::string name, Type* content);
        EValueType valueTypeID() const override;
        EType expectedReductionTypeID() const override;
    };
}