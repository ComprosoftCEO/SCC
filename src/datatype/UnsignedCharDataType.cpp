#include <DataType.h>

//
// Constructor
//
UnsignedCharDataType::UnsignedCharDataType(): PrimitiveDataType(PrimitiveType::UCHAR) {}

//
// Getters
//
size_t UnsignedCharDataType::size() const {
  return sizeof(C_UCHAR);
}

//
// Clone
//
UnsignedCharDataType* UnsignedCharDataType::clone() const {
  return new UnsignedCharDataType();
}
