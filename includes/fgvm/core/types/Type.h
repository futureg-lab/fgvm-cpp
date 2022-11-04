#pragma once

#include <string>

#include "../Constants.h"

namespace fgvm {
    // a Type should be able
    // to interrogate it's type id
    class Type {
    public:
        void* stored_value = nullptr;
        Type(size_t total_bits, EType type_id);
        EType getTypeId() const;
        size_t totalBits() const;

        virtual std::string storedValueAsString() const = 0;
    private:
        size_t total_bits = 0;
        EType type_id = EType::Unknown;
        std::string type_str = "Unknown";
    };
}