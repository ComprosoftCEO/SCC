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
