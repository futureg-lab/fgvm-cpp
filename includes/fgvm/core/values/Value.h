#pragma once

#include "../Constants.h"
#include "../Statement.h"

#include <string>

namespace fgvm {
    class Value : public Statement {
    public:
        std::string name = "";
        Value(std::string name);

        EStatementType stmtTypeId() const override;
        
        virtual EValueType valueTypeID() const = 0;
        virtual EType expectedReductionTypeID() const = 0;
    };
};