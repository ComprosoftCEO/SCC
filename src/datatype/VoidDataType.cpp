#include <DataType.h>
#include <Visitor.h>

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
// Visit
//
void VoidDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
VoidDataType* VoidDataType::clone() const {
  return new VoidDataType();
}
