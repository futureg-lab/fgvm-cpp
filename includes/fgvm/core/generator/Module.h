#pragma once
#include <map>
#include <string>
#include <set>

#include "../values/Value.h"
#include "../types/AtomicTypes.h"

namespace fgvm {
    class Statement;
    class Value;
    class Module {
    private:
        std::set<Statement*> ptr_pool;
    public:
        void addPool(Statement* ptr);

        unsigned long long getId();
        ~Module();
    };
}