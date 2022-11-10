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
        {EType::Bool, "bool"},
        {EType::Str, "str"},
        {EType::Void, "void"}
    };
    if (numIdStr.find(etype) == numIdStr.end())
        throw FGError::notExpected("type id " + std::to_string(etype) + " not recognized");
    return numIdStr[etype];
}

fgvm::Type* IRUtils::getTypeById(fgvm::EType etype)
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
        {EType::Bool, new BOOL()},
        {EType::Str, new STR()},
        {EType::Void, new VOID()}
    };
    if (numIdPtr.find(etype) == numIdPtr.end())
        throw FGError::notExpected("type id " + std::to_string(etype) + " not recognized");
    return numIdPtr[etype];
}

bool IRUtils::isNumber(fgvm::EType etype)
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
        {EType::Bool, new BOOL()},
    };
    if (numIdPtr.find(etype) == numIdPtr.end())
        throw FGError::notExpected("type id " + std::to_string(etype) + " not recognized");
    return numIdPtr[etype];
}

std::string IRUtils::prettifyIRSourceCode(std::string source)
{
    std::stringstream ss(source);
    std::string output = "";
    std::string line;
    int indent = 0;
    while (getline(ss, line)) {
        if (line.find('}') != std::string::npos)
            indent--;
        if (indent < 0)
            FGError::notExpected("invalid IR code, encountered a \"}\" without \"{\"");
        std::string cumul_space = "";
        for (int i = 0; i < indent; i++, cumul_space += "  ");
        output += cumul_space + line + "\n";
        if (line.find('{') != std::string::npos)
            indent++;
    }
    return output;
}

std::string IRUtils::join(std::vector<std::string>& list, std::string& sep)
{
    std::string res = "";
    for (size_t i = 0; i < list.size(); i++) {
        res += list[i];
        if ((i + 1) < list.size())
            res += sep;
    }
    return res;
}

std::string IRUtils::format(const std::string input, std::vector<std::string> params)
{
    std::string res = input;
    int count = 0;
    for (std::string& str : params) {
        std::regex reg("\\{" + std::to_string(count++) + "\\}");
        res = std::regex_replace(res, reg, str);
    }
    return res;
}