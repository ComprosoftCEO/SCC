#include <DataType.h>
#include <DataTypeFactory.h>

//
// Constructor
//
ArrayFactory::ArrayFactory(DataTypeFactory* sub_factory): ArrayFactory(sub_factory, nullptr) {}

ArrayFactory(DataTypeFactory* sub_factory, Expression* size):
  DataTypeFactory(sub_factory), size(size) {}

//
// Destructor
//
ArrayFactory::~ArrayFactory() {
  // Doesn't delete anything if resource has been moved
  delete (this->size);
}

//
// Build the aggregate type
//
DataType* ArrayFactory::build_aggregate(DataType* internal_type) {

  DataType* new_type = new ArrayDataType(internal_type, this->size);

  this->size = nullptr; // Resource has been moved
  return new_type;
}
