#include <DataType.h>
#include <DataTypeFactory.h>
#include <Expression.h>

//
// Constructor
//
ArrayFactory::ArrayFactory(): ArrayFactory(nullptr) {}

ArrayFactory::ArrayFactory(Expression* size): DataTypeFactory(nullptr), size(nullptr) {}

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
  DataType* new_type = new ArrayDataType(internal_type, this->size->clone());
  return new_type;
}
