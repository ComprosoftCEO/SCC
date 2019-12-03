#include <DataType.h>
#include <Visitor.h>

//
// Constructor
//
ShortDataType::ShortDataType(): PrimitiveDataType(PrimitiveType::SHORT) {}

//
// Getters
//
size_t ShortDataType::size() const {
  return sizeof(C_SHORT);
}

//
// Visit
//
void ShortDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
ShortDataType* ShortDataType::clone() const {
  return new ShortDataType();
}
