#include <DataType.h>

//
// Constructor
//
LongDoubleDataType::LongDoubleDataType(): PrimitiveDataType(PrimitiveType::LONGDOUBLE) {}

//
// Getters
//
size_t LongDoubleDataType::size() const {
  return sizeof(C_LONGDOUBLE);
}

//
// Clone
//
LongDoubleDataType* LongDoubleDataType::clone() const {
  return new LongDoubleDataType();
}
