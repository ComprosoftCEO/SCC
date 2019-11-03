#include <DataType.h>

//
// Constructor
//
CharDataType::CharDataType(): PrimitiveDataType(PrimitiveType::CHAR) {}

//
// Getters
//
size_t CharDataType::size() const {
  return CHAR_SIZE;
}

//
// Clone
//
CharDataType* CharDataType::clone() const {
  return new CharDataType();
}
