#include <DataType.h>

//
// Constructor
//
PrimitiveDataType::PrimitiveDataType(PrimitiveType primitive_type):
  DataType(ConcreteDataType::PRIMITIVE), primitive_type(primitive_type) {}

//
// Getters
//
PrimitiveType PrimitiveDataType::get_primitive_type() const {
  return this->primitive_type;
}

bool PrimitiveDataType::is_unsigned() const {
  return is_unsigned_type(this->primitive_type);
}

//
// Construct from the type
//
PrimitiveDataType* PrimitiveDataType::from_type(PrimitiveType type) {
  // Ugly. Replace with a jump table, maybe later...
  switch (type) {
    case PrimitiveType::VOID:
      return new VoidDataType();
    case PrimitiveType::CHAR:
      return new CharDataType();
    case PrimitiveType::UCHAR:
      return new UnsignedCharDataType();
    case PrimitiveType::SHORT:
      return new ShortDataType();
    case PrimitiveType::USHORT:
      return new UnsignedShortDataType();
    case PrimitiveType::INT:
      return new IntDataType();
    case PrimitiveType::UINT:
      return new UnsignedIntDataType();
    case PrimitiveType::LONG:
      return new LongDataType();
    case PrimitiveType::ULONG:
      return new UnsignedLongDataType();
    case PrimitiveType::LONGLONG:
      return new LongLongDataType();
    case PrimitiveType::ULONGLONG:
      return new UnsignedLongLongDataType();
    case PrimitiveType::FLOAT:
      return new FloatDataType();
    case PrimitiveType::DOUBLE:
      return new DoubleDataType();
    case PrimitiveType::LONGDOUBLE:
      return new LongDoubleDataType();
    default:
      return nullptr;
  }
}
