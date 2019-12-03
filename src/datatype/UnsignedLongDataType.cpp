#include <DataType.h>
#include <Visitor.h>

//
// Constructor
//
UnsignedIntDataType::UnsignedIntDataType(): PrimitiveDataType(PrimitiveType::UINT) {}

//
// Getters
//
size_t UnsignedIntDataType::size() const {
  return sizeof(C_UINT);
}

//
// Visit
//
void UnsignedLongDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
UnsignedIntDataType* UnsignedIntDataType::clone() const {
  return new UnsignedIntDataType();
}
