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
        {EType::Void, "void"},
        {EType::Ref, "ref"}
    };
    FGError::ASSERT(numIdStr.find(etype) != numIdStr.end());
    return numIdStr[etype];
}
