#pragma once

#include "../Constants.h"

#include "FGError.h"
#include <sstream>

#include <map>

namespace IRUtils {
    const std::string enumTypeToStr(fgvm::EType etype);

    template<typename T>
    std::string stringifyPtrValue(void* value);

    template<typename T>
    T strToValue(std::string str);

    template<typename T>
    void* makePointerOutOf(T value);
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
    FGError::NOT_NULL(value);
    return std::to_string(*static_cast<T*>(value));
}

template<typename T>
void* IRUtils::makePointerOutOf(T value)
{
    T* addr = (T*) malloc(sizeof(T));
    addr[0] = value;
    return (void*)addr;
}