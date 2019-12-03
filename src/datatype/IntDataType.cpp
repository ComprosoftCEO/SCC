#include <DataType.h>
#include <Visitor.h>

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
// Visit
//
void IntDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
IntDataType* IntDataType::clone() const {
  return new IntDataType();
}
