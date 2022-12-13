#pragma once

#include <string>

#include "../Constants.h"

namespace fgvm {
    // a Type should be able
    // to interrogate it's type id
    class Type {
    public:
        std::string stored_value = "__undefined__";
        Type(size_t total_bits, EType type_id);
        EType getTypeId() const;
        size_t totalBits() const;

        virtual std::string storedValueAsString();
    private:
        size_t total_bits = 0;
        EType type_id = EType::Unknown;
        std::string type_str = "Unknown";
    };
}