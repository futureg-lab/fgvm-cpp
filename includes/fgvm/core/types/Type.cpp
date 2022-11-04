#include "Type.h"

fgvm::Type::Type(size_t total_bits, EType type_id)
{
	this->total_bits = total_bits;
	this->type_id = type_id;
}

fgvm::EType fgvm::Type::getTypeId() const
{
	return type_id;
}

size_t fgvm::Type::totalBits() const
{
	return total_bits;
}