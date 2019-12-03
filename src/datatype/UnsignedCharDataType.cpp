#include <DataType.h>
#include <Visitor.h>

//
// Constructor
//
UnsignedCharDataType::UnsignedCharDataType(): PrimitiveDataType(PrimitiveType::UCHAR) {}

//
// Getters
//
size_t UnsignedCharDataType::size() const {
  return sizeof(C_UCHAR);
}

//
// Visit
//
void UnsignedCharDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
UnsignedCharDataType* UnsignedCharDataType::clone() const {
  return new UnsignedCharDataType();
}
