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
	stored_value = IRUtils::makePointerOutOf<uint8_t>(value);
}

std::string fgvm::U8::storedValueAsString() const
{
	return IRUtils::stringifyPtrValue<uint8_t>(stored_value);
}

// Uint16

fgvm::U16::U16()
	: Type(16, EType::Uint16)
{
}

fgvm::U16::U16(uint16_t value)
	: Type(16, EType::Uint16)
{
	stored_value = IRUtils::makePointerOutOf<uint16_t>(value);
}

std::string fgvm::U16::storedValueAsString() const
{
	return IRUtils::stringifyPtrValue<uint16_t>(stored_value);
}

// Uint32
fgvm::U32::U32()
	: Type(32, EType::Uint16)
{
}

fgvm::U32::U32(uint32_t value)
	: Type(32, EType::Uint32)
{
	stored_value = IRUtils::makePointerOutOf<uint32_t>(value);
}

std::string fgvm::U32::storedValueAsString() const
{
	int x = *(int*)stored_value;
	return IRUtils::stringifyPtrValue<uint32_t>(&x);
}


// Uint64
fgvm::U64::U64()
	: Type(64, EType::Uint64)
{
}

fgvm::U64::U64(uint64_t value)
	: Type(64, EType::Uint64)
{
	stored_value = IRUtils::makePointerOutOf<uint64_t>(value);
}

std::string fgvm::U64::storedValueAsString() const
{
	return IRUtils::stringifyPtrValue<uint64_t>(stored_value);
}


// INT8
fgvm::I8::I8()
	: Type(8, EType::Int8)
{
}

fgvm::I8::I8(int8_t value)
	: Type(8, EType::Int8)
{
	stored_value = IRUtils::makePointerOutOf<int8_t>(value);
}

std::string fgvm::I8::storedValueAsString() const
{
	return IRUtils::stringifyPtrValue<int8_t>(stored_value);
}


// INT16
fgvm::I16::I16()
	: Type(16, EType::Int16)
{
}

fgvm::I16::I16(int16_t value)
	: Type(16, EType::Int16)
{
	stored_value = IRUtils::makePointerOutOf<int16_t>(value);
}

std::string fgvm::I16::storedValueAsString() const
{
	return IRUtils::stringifyPtrValue<int16_t>(stored_value);
}

// INT32
fgvm::I32::I32()
	: Type(32, EType::Int32)
{
}

fgvm::I32::I32(int32_t value)
	: Type(32, EType::Int32)
{
	stored_value = IRUtils::makePointerOutOf<int32_t>(value);
}

std::string fgvm::I32::storedValueAsString() const
{
	int x = *(int*)stored_value;
	return IRUtils::stringifyPtrValue<int32_t>(&x);
}

// INT64
fgvm::I64::I64()
	: Type(64, EType::Int64)
{
}

fgvm::I64::I64(int64_t value)
	: Type(64, EType::Int64)
{
	stored_value = IRUtils::makePointerOutOf<int64_t>(value);
}

std::string fgvm::I64::storedValueAsString() const
{
	return IRUtils::stringifyPtrValue<int64_t>(stored_value);
}

// FLOAT32
fgvm::F32::F32()
	: Type(32, EType::Float32)
{
}

fgvm::F32::F32(float value)
	: Type(32, EType::Float32)
{
	stored_value = IRUtils::makePointerOutOf<float>(value);
}

std::string fgvm::F32::storedValueAsString() const
{
	return IRUtils::stringifyPtrValue<float>(stored_value);
}


// FLOAT64
fgvm::F64::F64()
	: Type(64, EType::Float64)
{
}

fgvm::F64::F64(double value)
	: Type(64, EType::Float64)
{
	stored_value = IRUtils::makePointerOutOf<double>(value);
}

std::string fgvm::F64::storedValueAsString() const
{
	return IRUtils::stringifyPtrValue<double>(stored_value);
}


// BOOL
fgvm::BOOL::BOOL()
	: Type(1, EType::Bool)
{
}

fgvm::BOOL::BOOL(bool value)
	: Type(1, EType::Bool)
{
	stored_value = IRUtils::makePointerOutOf<bool>(value);
}

std::string fgvm::BOOL::storedValueAsString() const
{
	return IRUtils::stringifyPtrValue<bool>(stored_value);
}


// Str
fgvm::STR::STR()
	: Type(0, EType::Str)
{
}

fgvm::STR::STR(const char* value)
	: Type(strlen(value) * 8, EType::Str)
{
	stored_value = (void*) value;
}

std::string fgvm::STR::storedValueAsString() const
{
	std::string value = "";
	size_t len = totalBits() / 8;
	
	char* addr = (char*) stored_value;
	for (size_t i = 0; i < len; value += addr[i], i++);

	return value;
}


// Void
fgvm::VOID::VOID()
	: Type(0, EType::Void)
{
	stored_value = nullptr;
}

std::string fgvm::VOID::storedValueAsString() const
{
	return "__void__";
}