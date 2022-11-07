#pragma once

#include "SARRefValue.h"
#include "FunctionCustomCallValue.h"

namespace fgvm {
    // %value_name = func_name type args
    class FunctionCallValue : public FunctionCustomCallValue {
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