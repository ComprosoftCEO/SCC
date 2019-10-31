#include <DataTypeFactory.h>
#include <Declarator.h>

//
// Default Constructor
//
AbstractDeclarator::AbstractDeclarator(): factory(nullptr) {}

//
// Destructor
//
AbstractDeclarator::~AbstractDeclarator() {
  delete (this->factory);
}

//
// Add a factory to the set of factories
//
void AbstractDeclarator::add_factory(const DataTypeFactoryFactory& build_factory) {
  this->factory = build_factory(this->factory);
}

//
// Build the data type
//
DataType* AbstractDeclarator::build_data_type(DataType* internal_type) const {

  if (this->factory != nullptr) {
    // Tail-end recursion
    return this->factory->build_data_type(internal_type);
  }

  return internal_type;
}
