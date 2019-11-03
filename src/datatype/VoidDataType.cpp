#include <DataType.h>

//
// Constructor
//
VoidDataType::VoidDataType(): PrimitiveDataType(PrimitiveType::VOID) {}

//
// Getters
//
size_t VoidDataType::size() const {
  return VOID_SIZE; // Void has no size
}

//
// Clone
//
VoidDataType* VoidDataType::clone() const {
  return new VoidDataType();
}
