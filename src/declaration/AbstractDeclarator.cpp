#include <DataTypeFactory.h>
#include <Declaration.h>

//
// Constructor
//
AbstractDeclarator::AbstractDeclarator(): AbstractDeclarator(nullptr) {}

AbstractDeclarator::AbstractDeclarator(DataTypeFactory* sub_factory): sub_factory(sub_factory) {}

//
// Destructor
//
AbstractDeclarator::~AbstractDeclarator() {
  delete (this->sub_factory);
}

//
// Add a factory to the set of factories
//
void AbstractDeclarator::add_factory(DataTypeFactory* new_factory) {
  new_factory->sub_factory = this->sub_factory;
  this->sub_factory        = new_factory;
}

//
// Build the data type
//
DataType* AbstractDeclarator::build_data_type(DataType* internal_type) const {

  if (this->sub_factory != nullptr) {
    // Tail-end recursion
    return this->sub_factory->build_data_type(internal_type);
  }

  return internal_type;
}
