#pragma once

#include <string>
#include "../Constants.h"
#include "../generator/Module.h"
#include "../utils/FGError.h"

namespace fgvm {
    class Module;

    class Value {
    public:
        std::string name = "";
        Module* module_owner = nullptr;
        Value(std::string name, Module* module_owner);
        virtual EValueType valueTypeID() const = 0;
        virtual EType expectedReductionTypeID() const = 0;
    };
};