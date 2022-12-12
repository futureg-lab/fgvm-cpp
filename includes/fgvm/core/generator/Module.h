#pragma once

#include "../Statement.h"

#include <string>
#include <set>

namespace fgvm {

    class Module {
    private:
        std::set<Statement*> ptr_pool;
    public:
        void addPool(Statement* ptr);
        unsigned long long getId();
        ~Module();
    };
}