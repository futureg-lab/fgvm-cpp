#pragma once
#include <map>
#include <string>
#include <set>

#include "../Statement.h"

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