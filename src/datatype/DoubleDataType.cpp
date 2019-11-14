#include <DataType.h>

//
// Constructor
//
DoubleDataType::DoubleDataType(): PrimitiveDataType(PrimitiveType::DOUBLE) {}

//
// Getters
//
size_t DoubleDataType::size() const {
  return sizeof(C_DOUBLE);
}

//
// Clone
//
DoubleDataType* DoubleDataType::clone() const {
  return new DoubleDataType();
}
