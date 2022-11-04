#pragma once
#include <map>
#include <string>

#include "../values/Value.h"
#include "../types/AtomicTypes.h"

namespace fgvm {
    class Value;
    class Module {
    public:
        std::map<std::string, Value*> variables;

        void addVariable(std::string name, Value* value);

        Value* getVariable(std::string name);

        unsigned long long getId();
        ~Module();
    };
}