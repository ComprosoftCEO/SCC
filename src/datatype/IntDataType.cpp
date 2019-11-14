#include <DataType.h>

//
// Constructor
//
IntDataType::IntDataType(): PrimitiveDataType(PrimitiveType::INT) {}

//
// Getters
//
size_t IntDataType::size() const {
  return sizeof(C_INT);
}

//
// Clone
//
IntDataType* IntDataType::clone() const {
  return new IntDataType();
}
