#pragma once

#include "Value.h"
#include "SARRefValue.h"

namespace fgvm {
    // %value_name = func_name type args
    class FunctionCallValue : public Value {
    public:
        std::string called_func_name;
        std::vector<Value*> arg_inputs;
        
        FunctionCallValue(
            std::string assign_name,
            std::string called_func_name,
            std::vector<Value*> arg_inputs);

        EValueType valueTypeID() const override;
        EType expectedReductionTypeID() const override;
    };
};