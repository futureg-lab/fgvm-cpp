#pragma once

#include "Value.h"
#include "SARRefValue.h"

namespace fgvm {
    // %value_name = func_name type args
    class FunctionCustomCallValue : public Value {
    private:
        EType type_output_hint = EType::Void;
    public:
        std::string called_func_name;
        std::vector<Value*> arg_inputs;
        
        FunctionCustomCallValue(
            std::string assign_name,
            std::string called_func_name,
            std::vector<Value*> arg_inputs,
            EType type_output_hint
            );
        virtual void setReductionTypeId(EType type_output_hint);
        virtual EValueType valueTypeID() const override;
        virtual EType expectedReductionTypeID() const override;
    };
};