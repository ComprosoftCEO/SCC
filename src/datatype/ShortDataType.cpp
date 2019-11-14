#include <DataType.h>

//
// Constructor
//
ShortDataType::ShortDataType(): PrimitiveDataType(PrimitiveType::SHORT) {}

//
// Getters
//
size_t ShortDataType::size() const {
  return sizeof(C_SHORT);
}

//
// Clone
//
ShortDataType* ShortDataType::clone() const {
  return new ShortDataType();
}
