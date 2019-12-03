#include <DataType.h>
#include <Visitor.h>

//
// Constructor
//
LongDataType::LongDataType(): PrimitiveDataType(PrimitiveType::LONG) {}

//
// Getters
//
size_t LongDataType::size() const {
  return sizeof(C_LONG);
}

//
// Visit
//
void LongDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
LongDataType* LongDataType::clone() const {
  return new LongDataType();
}
