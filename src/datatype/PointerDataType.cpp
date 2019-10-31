#include <DataType.h>

//
// Constructor
//
PointerDataType::PointerDataType(DataType* point_type):
  DataType(ConcreteDataType::POINTER), point_type(point_type) {}

//
// Destructor
//
PointerDataType::~PointerDataType() {
  delete (this->point_type);
}

//
// Getters
//
DataType* PointerDataType::get_point_type() const {
  return this->point_type;
}

size_t PointerDataType::size() const {
  return POINTER_SIZE;
}

//
// Clone
//
PointerDataType* PointerDataType::clone() const {
  return new PointerDataType(this->point_type->clone());
}
