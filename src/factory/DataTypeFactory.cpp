#include <DataTypeFactory.h>

//
// Constructor
//
DataTypeFactory::DataTypeFactory(): DataTypeFactory(nullptr) {}

DataTypeFactory::DataTypeFactory(DataTypeFactory* sub_factory): sub_factory(sub_factory) {}

//
// Destructor
//
DataTypeFactory::~DataTypeFactory() {
  delete (this->sub_factory);
}

//
// Getters
//
DataTypeFactory* DataTypeFactory::get_sub_factory() const {
  return this->sub_factory;
}

//
// Update the sub factory
//
void DataTypeFactory::set_sub_factory(DataTypeFactory* sub_factory) {
  delete (this->sub_factory);
  this->sub_factory = sub_factory;
}

//
// Build the data type
//
DataType* DataTypeFactory::build_data_type(DataType* internal_type) {

  DataType* new_type = this->build_aggregate(internal_type);

  if (this->sub_factory != nullptr) {
    // Tail-end recursion
    return this->sub_factory->build_data_type(new_type);
  }

  return new_type;
}
