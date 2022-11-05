#pragma once

#include <string>
#include "../Constants.h"
#include "../generator/Module.h"
#include "../utils/FGError.h"
#include "../Statement.h"

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