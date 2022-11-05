#pragma once
#include <map>
#include <string>

#include "../values/Value.h"
#include "../types/AtomicTypes.h"

namespace fgvm {
    class Statement;
    class Value;
    class Module {
    private:
        std::vector<Statement*> ptr_pool;
    public:
        std::map<std::string, Value*> variables;

        void addVariable(std::string name, Value* value);
        void addPool(Statement* ptr);

        Value* getVariable(std::string name);

        unsigned long long getId();
        ~Module();
    };
}