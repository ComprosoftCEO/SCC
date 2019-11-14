#include <DataType.h>

//
// Constructor
//
CharDataType::CharDataType(): PrimitiveDataType(PrimitiveType::CHAR) {}

//
// Getters
//
size_t CharDataType::size() const {
  return sizeof(C_CHAR);
}

//
// Clone
//
CharDataType* CharDataType::clone() const {
  return new CharDataType();
}
