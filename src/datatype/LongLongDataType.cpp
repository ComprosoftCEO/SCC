#include <DataType.h>
#include <Visitor.h>

//
// Constructor
//
LongLongDataType::LongLongDataType(): PrimitiveDataType(PrimitiveType::LONGLONG) {}

//
// Getters
//
size_t LongLongDataType::size() const {
  return sizeof(C_LONGLONG);
}

//
// Visit
//
void LongLongDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
LongLongDataType* LongLongDataType::clone() const {
  return new LongLongDataType();
}
