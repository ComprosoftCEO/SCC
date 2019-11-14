#include <DataType.h>

//
// Constructor
//
FloatDataType::FloatDataType(): PrimitiveDataType(PrimitiveType::FLOAT) {}

//
// Getters
//
size_t FloatDataType::size() const {
  return sizeof(C_FLOAT);
}

//
// Clone
//
FloatDataType* FloatDataType::clone() const {
  return new FloatDataType();
}
