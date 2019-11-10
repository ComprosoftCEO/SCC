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
// Downcast to declaration
//
bool AbstractDeclaration::has_name() const {
  return false;
}

Declaration* AbstractDeclaration::to_declaration() {
  return dynamic_cast<Declaration*>(this);
}

//
// Clone
//
AbstractDeclaration* AbstractDeclaration::clone() const {
  return new AbstractDeclaration(DataType::clone(this->type));
}
