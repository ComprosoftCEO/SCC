#include <DataType.h>
#include <Visitor.h>

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
// Visit
//
void FloatDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
FloatDataType* FloatDataType::clone() const {
  return new FloatDataType();
}
