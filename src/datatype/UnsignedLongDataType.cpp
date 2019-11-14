#include <DataType.h>

//
// Constructor
//
UnsignedIntDataType::UnsignedIntDataType(): PrimitiveDataType(PrimitiveType::UINT) {}

//
// Getters
//
size_t UnsignedIntDataType::size() const {
  return sizeof(C_UINT);
}

//
// Clone
//
UnsignedIntDataType* UnsignedIntDataType::clone() const {
  return new UnsignedIntDataType();
}
