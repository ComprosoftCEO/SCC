#include <DataType.h>
#include <Expression.h>
#include <Visitor.h>

//
// Constructor
//
ArrayDataType::ArrayDataType(DataType* type): ArrayDataType(type, nullptr) {}

ArrayDataType::ArrayDataType(DataType* type, class Expression* array_size):
  DataType(ConcreteDataType::ARRAY), type(type), array_size(array_size) {}

//
// Getters
//
DataType* ArrayDataType::get_array_type() const {
  return this->type;
}

Expression* ArrayDataType::get_array_size() const {
  return this->array_size;
}

size_t ArrayDataType::size() const {
  return 0;
}

//
// Visit
//
void ArrayDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
DataType* ArrayDataType::clone() const {
  return new ArrayDataType(this->type->clone(),
                           this->array_size ? this->array_size->clone() : nullptr);
}
