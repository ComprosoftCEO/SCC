#include <DataType.h>

//
// Constructor
//
IntDataType::IntDataType(): PrimitiveDataType(PrimitiveType::INT) {}

//
// Getters
//
size_t IntDataType::size() const {
  return INT_SIZE;
}

//
// Clone
//
IntDataType* IntDataType::clone() const {
  return new IntDataType();
}
