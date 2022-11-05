#include "IRUtils.h"



const std::string IRUtils::enumTypeToStr(fgvm::EType etype)
{
    using namespace fgvm;
    std::map<unsigned int, const std::string> numIdStr = {
        {EType::Uint8, "u8"},
        {EType::Uint16, "u16"},
        {EType::Uint64, "u64"},
        {EType::Uint32, "u32"},
        {EType::Int8, "i8"},
        {EType::Int16, "i16"},
        {EType::Int32, "i32"},
        {EType::Int64, "i64"},
        {EType::Float32, "f32"},
        {EType::Float64, "f64"},
        {EType::Str, "str"},
        {EType::Void, "void"}
    };
    FGError::ASSERT(numIdStr.find(etype) != numIdStr.end());
    return numIdStr[etype];
}

fgvm::Type* IRUtils::getTypeById(fgvm::EType type)
{
    using namespace fgvm;
    std::map<unsigned int, fgvm::Type*> numIdPtr = {
        {EType::Uint8, new U8()},
        {EType::Uint16, new U16()},
        {EType::Uint64, new U64()},
        {EType::Uint32, new U32()},
        {EType::Int8, new I8()},
        {EType::Int16, new I16()},
        {EType::Int32, new I32()},
        {EType::Int64, new I64()},
        {EType::Float32, new F32()},
        {EType::Float64, new F64()},
        {EType::Str, new STR()},
        {EType::Void, new VOID()}
    };

    FGError::ASSERT(numIdPtr.find(type) != numIdPtr.end());
    return numIdPtr[type];
}
