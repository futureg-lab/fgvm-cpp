#include "AtomicTypes.h"
#include "../utils/FGError.h"
#include "../utils/IRUtils.h"

//
// unsigned int
//

fgvm::U8::U8()
	: Type(8, EType::Uint8)
{
}

// Uint8
fgvm::U8::U8(uint8_t value)
	: Type(8, EType::Uint8)
{
	stored_value = std::to_string(value);
}

// Uint16

fgvm::U16::U16()
	: Type(16, EType::Uint16)
{
}

fgvm::U16::U16(uint16_t value)
	: Type(16, EType::Uint16)
{
	stored_value = std::to_string(value);
}

// Uint32
fgvm::U32::U32()
	: Type(32, EType::Uint16)
{
}

fgvm::U32::U32(uint32_t value)
	: Type(32, EType::Uint32)
{
	stored_value = std::to_string(value);
}


// Uint64
fgvm::U64::U64()
	: Type(64, EType::Uint64)
{
}

fgvm::U64::U64(uint64_t value)
	: Type(64, EType::Uint64)
{
	stored_value = std::to_string(value);
}


// INT8
fgvm::I8::I8()
	: Type(8, EType::Int8)
{
}

fgvm::I8::I8(int8_t value)
	: Type(8, EType::Int8)
{
	stored_value = std::to_string(value);
}


// INT16
fgvm::I16::I16()
	: Type(16, EType::Int16)
{
}

fgvm::I16::I16(int16_t value)
	: Type(16, EType::Int16)
{
	stored_value = std::to_string(value);
}

// INT32
fgvm::I32::I32()
	: Type(32, EType::Int32)
{
}

fgvm::I32::I32(int32_t value)
	: Type(32, EType::Int32)
{
	stored_value = std::to_string(value);
}

// INT64
fgvm::I64::I64()
	: Type(64, EType::Int64)
{
}

fgvm::I64::I64(int64_t value)
	: Type(64, EType::Int64)
{
	stored_value = std::to_string(value);
}

// FLOAT32
fgvm::F32::F32()
	: Type(32, EType::Float32)
{
}

fgvm::F32::F32(float value)
	: Type(32, EType::Float32)
{
	stored_value = std::to_string(value);
}


// FLOAT64
fgvm::F64::F64()
	: Type(64, EType::Float64)
{
}

fgvm::F64::F64(double value)
	: Type(64, EType::Float64)
{
	stored_value = std::to_string(value);
}


// BOOL
fgvm::BOOL::BOOL()
	: Type(1, EType::Bool)
{
}

fgvm::BOOL::BOOL(bool value)
	: Type(1, EType::Bool)
{
	stored_value = std::to_string(value);
}


// Str
fgvm::STR::STR()
	: Type(0, EType::Str)
{
}


fgvm::STR::STR(const char* value)
	: Type(strlen(value) * 8, EType::Str)
{
	stored_value = value;
}

// Void
fgvm::VOID::VOID()
	: Type(0, EType::Void)
{
	stored_value = "__void__";
}