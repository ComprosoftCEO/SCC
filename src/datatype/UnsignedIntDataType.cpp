#include <DataType.h>
#include <Visitor.h>

//
// Constructor
//
UnsignedLongDataType::UnsignedLongDataType(): PrimitiveDataType(PrimitiveType::ULONG) {}

//
// Getters
//
size_t UnsignedLongDataType::size() const {
  return sizeof(C_ULONG);
}

//
// Visit
//
void UnsignedIntDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
UnsignedLongDataType* UnsignedLongDataType::clone() const {
  return new UnsignedLongDataType();
}
