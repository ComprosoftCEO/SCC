#include <DataType.h>
#include <Visitor.h>

//
// Constructor
//
CharDataType::CharDataType(): PrimitiveDataType(PrimitiveType::CHAR) {}

//
// Getters
//
size_t CharDataType::size() const {
  return sizeof(C_CHAR);
}

//
// Visit
//
void CharDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
CharDataType* CharDataType::clone() const {
  return new CharDataType();
}
