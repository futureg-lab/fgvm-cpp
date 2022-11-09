#pragma once
#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <vector>

#include "Type.h"
#include "../values/Value.h"


namespace fgvm {
    //
    // Unsigned
    // 

    class U8 : public Type {
    public:
        U8();
        U8(uint8_t value);
        std::string storedValueAsString() const override;
    };

    class U16 : public Type {
    public:
        U16();
        U16(uint16_t value);
        std::string storedValueAsString() const override;
    };

    class U32 : public Type {
    public:
        U32();
        U32(uint32_t value);
        std::string storedValueAsString() const override;
    };

    class U64 : public Type {
    public:
        U64();
        U64(uint64_t value);
        std::string storedValueAsString() const override;
    };


    //
    // Signed
    //

    class I8 : public Type {
    public:
        I8();
        I8(int8_t value);
        std::string storedValueAsString() const override;
    };

    class I16 : public Type {
    public:
        I16();
        I16(int16_t value);
        std::string storedValueAsString() const override;
    };

    class I32 : public Type {
    public:
        I32();
        I32(int32_t value);
        std::string storedValueAsString() const override;
    };

    class I64 : public Type {
    public:
        I64();
        I64(int64_t value);
        std::string storedValueAsString() const override;
    };


    //
    // Float
    //

    class F32 : public Type {
    public:
        F32();
        F32(float value);
        std::string storedValueAsString() const override;
    };

    class F64 : public Type {
    public:
        F64();
        F64(double value);
        std::string storedValueAsString() const override;
    };

    // Bool
    class BOOL : public Type {
    public:
        BOOL();
        BOOL(bool value);
        std::string storedValueAsString() const override;
    };

    // str
    class STR : public Type {
    public:
        STR();
        STR(const char* value);
        std::string storedValueAsString() const override;
    };

    // void
    class VOID : public Type {
    public:
        VOID();
        std::string storedValueAsString() const override;
    };


    class LIST : public Type {
    public:
        LIST();
        std::string storedValueAsString() const override;
    };
}