#include <DataType.h>
#include <visitor.h>

//
// Constructor
//
UnsignedShortDataType::UnsignedShortDataType(): PrimitiveDataType(PrimitiveType::USHORT) {}

//
// Getters
//
size_t UnsignedShortDataType::size() const {
  return sizeof(C_USHORT);
}

//
// Visit
//
void UnsignedShortDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
UnsignedShortDataType* UnsignedShortDataType::clone() const {
  return new UnsignedShortDataType();
}
