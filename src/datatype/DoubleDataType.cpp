#include <DataType.h>
#include <Visitor.h>

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
// Visit
//
void DoubleDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
DoubleDataType* DoubleDataType::clone() const {
  return new DoubleDataType();
}
