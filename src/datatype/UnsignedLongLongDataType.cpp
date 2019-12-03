#include <DataType.h>
#include <Visitor.h>

//
// Constructor
//
UnsignedLongLongDataType::UnsignedLongLongDataType(): PrimitiveDataType(PrimitiveType::ULONGLONG) {}

//
// Getters
//
size_t UnsignedLongLongDataType::size() const {
  return sizeof(C_ULONGLONG);
}

//
// Visit
//
void UnsignedLongLongDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
UnsignedLongLongDataType* UnsignedLongLongDataType::clone() const {
  return new UnsignedLongLongDataType();
}
