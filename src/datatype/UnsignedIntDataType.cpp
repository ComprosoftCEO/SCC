#include <DataType.h>

//
// Constructor
//
UnsignedLongDataType::UnsignedLongDataType(): PrimitiveDataType(PrimitiveType::ULONG) {}

//
// Getters
//
size_t UnsignedLongDataType::size() const {
  return sizeof(C_ULONG);
}

//
// Clone
//
UnsignedLongDataType* UnsignedLongDataType::clone() const {
  return new UnsignedLongDataType();
}
