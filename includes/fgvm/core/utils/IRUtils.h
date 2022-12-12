#pragma once

#include "../Constants.h"

#include "FGError.h"
#include <sstream>

#include <map>
#include <regex>
#include <iterator>

#include "../types/AtomicTypes.h"

namespace IRUtils {
    const std::string enumTypeToStr(fgvm::EType etype);
    fgvm::Type* getTypeById(fgvm::EType type);
    
    bool isNumber(fgvm::EType type);

    std::string prettifyIRSourceCode(std::string source);

    // a1, a2, .. aN => a1 sep a2 sep a3 sep ... sep aN
    std::string join(std::vector<std::string>& list, std::string& sep);

    // input "hello {0} {1"}, params = "world", "!" => "hello world !"
    std::string format(const std::string input, std::vector<std::string> params);

    template<typename T>
    std::string stringifyPtrValue(void* value);

    template<typename T>
    T strToValue(std::string str);

    template<typename T>
    void* makePointerOutOf(T value);

    template<typename T>
    void cleanupVoidPointer(void* value);
}

template<typename T>
T IRUtils::strToValue(std::string str)
{
    T value{};
    std::stringstream ss(str);
    ss >> value;
    return value;
}

template<typename T>
std::string IRUtils::stringifyPtrValue(void* value)
{
    return std::to_string(*static_cast<T*>(value));
}

template<typename T>
void* IRUtils::makePointerOutOf(T value)
{
    T* addr = (T*) malloc(sizeof(T));
    addr[0] = value;
    return (void*)addr;
}

template<typename T>
void IRUtils::cleanupVoidPointer(void* value)
{
    if (value == nullptr)
        return;
    delete static_cast<T*>(value);
}
