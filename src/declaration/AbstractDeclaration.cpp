#include <DataType.h>
#include <Declaration.h>

//
// Constructor
//
AbstractDeclaration::AbstractDeclaration(DataType* type): type(type) {}

//
// Destructor
//
AbstractDeclaration::~AbstractDeclaration() {
  delete (this->type);
}

//
// Getters
//
DataType* AbstractDeclaration::get_type() const {
  return this->type;
}

//
// Clone
//
AbstractDeclaration* AbstractDeclaration::clone() const {
  return new AbstractDeclaration(DataType::clone(this->type));
}
