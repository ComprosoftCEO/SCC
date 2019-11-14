#include <DataType.h>

//
// Constructor
//
UnsignedLongLongDataType::UnsignedLongLongDataType(): PrimitiveDataType(PrimitiveType::ULONGLONG) {}

//
// Getters
//
size_t UnsignedLongLongDataType::size() const {
  return sizeof(C_ULONGLONG);
}

//
// Clone
//
UnsignedLongLongDataType* UnsignedLongLongDataType::clone() const {
  return new UnsignedLongLongDataType();
}
