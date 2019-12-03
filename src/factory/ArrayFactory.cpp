#include <DataType.h>
#include <DataTypeFactory.h>
#include <Expression.h>

//
// Constructor
//
ArrayFactory::ArrayFactory(): ArrayFactory(nullptr, nullptr) {}

ArrayFactory::ArrayFactory(DataTypeFactory* sub_factory): ArrayFactory(sub_factory, nullptr) {}

ArrayFactory::ArrayFactory(Expression* size): ArrayFactory(nullptr, size) {}

ArrayFactory::ArrayFactory(DataTypeFactory* sub_factory, Expression* size):
  DataTypeFactory(sub_factory), size(size) {}

//
// Destructor
//
ArrayFactory::~ArrayFactory() {
  delete (this->size);
}

//
// Build the aggregate type
//
DataType* ArrayFactory::build_aggregate(DataType* internal_type) {
  return new ArrayDataType(internal_type, Expression::clone(this->size));
}
