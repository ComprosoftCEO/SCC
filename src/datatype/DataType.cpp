#include <DataType.h>

//
// Constructor
//
DataType::DataType(ConcreteDataType concrete_type): concrete_type(concrete_type) {}

//
// Get concrete type
//
ConcreteDataType DataType::get_concrete_type() const {
  return this->concrete_type;
}

//
// Static clone method
//
DataType* DataType::clone(DataType* type) {
  return type != nullptr ? type->clone() : nullptr;
}
