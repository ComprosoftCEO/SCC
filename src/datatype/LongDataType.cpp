#include <DataType.h>

//
// Constructor
//
LongDataType::LongDataType(): PrimitiveDataType(PrimitiveType::LONG) {}

//
// Getters
//
size_t LongDataType::size() const {
  return LONG_SIZE;
}

//
// Clone
//
LongDataType* LongDataType::clone() const {
  return new LongDataType();
}
