#pragma once

#include "../Statement.h"

#include "NameGenerator.h"

#include <string>
#include <memory>
#include <set>

namespace fgvm {

    class Module {
    private:
        std::set<Statement*> ptr_pool;
    public:
        std::unique_ptr<NameGenerator> symbols = std::make_unique<NameGenerator>();

        void addPool(Statement* ptr);
        unsigned long long getId();
        ~Module();
    };
}