#include <DataType.h>

//
// Constructor
//
LongLongDataType::LongLongDataType(): PrimitiveDataType(PrimitiveType::LONGLONG) {}

//
// Getters
//
size_t LongLongDataType::size() const {
  return sizeof(C_LONGLONG);
}

//
// Clone
//
LongLongDataType* LongLongDataType::clone() const {
  return new LongLongDataType();
}
