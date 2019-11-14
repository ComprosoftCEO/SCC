#include <DataType.h>

//
// Constructor
//
LongDataType::LongDataType(): PrimitiveDataType(PrimitiveType::LONG) {}

//
// Getters
//
size_t LongDataType::size() const {
  return sizeof(C_LONG);
}

//
// Clone
//
LongDataType* LongDataType::clone() const {
  return new LongDataType();
}
