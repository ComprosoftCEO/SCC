#include <DataType.h>

//
// Constructor
//
UnsignedShortDataType::UnsignedShortDataType(): PrimitiveDataType(PrimitiveType::USHORT) {}

//
// Getters
//
size_t UnsignedShortDataType::size() const {
  return sizeof(C_USHORT);
}

//
// Clone
//
UnsignedShortDataType* UnsignedShortDataType::clone() const {
  return new UnsignedShortDataType();
}
