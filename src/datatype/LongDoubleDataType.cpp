#include <DataType.h>
#include <Visitor.h>

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
// Visit
//
void LongDoubleDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}
//
// Clone
//
LongDoubleDataType* LongDoubleDataType::clone() const {
  return new LongDoubleDataType();
}
