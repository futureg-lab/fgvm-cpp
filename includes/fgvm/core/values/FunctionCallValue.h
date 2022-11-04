#pragma once

#include "Value.h"

namespace fgvm {
    class Module;

    // %value_name = func_name type args
    class FunctionCallValue : public Value {
    public:
        std::string called_func_name;
        std::vector<Value*> arg_inputs;
        
        FunctionCallValue(
            std::string assign_name,
            std::string called_func_name,
            std::vector<Value*> arg_inputs,
            Module* module_owner);

        EValueType valueTypeID() const override;
        EType expectedReductionTypeID() const override;
    };
};