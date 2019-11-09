#include <DataType.h>
#include <Declaration.h>

//
// Constructor
//
Declaration::Declaration(DataType* type, const std::string& name):
  AbstractDeclaration(type), name(name) {}

//
// Getters
//
const std::string& Declaration::get_name() const {
  return this->name;
}

//
// Clone
//
Declaration* Declaration::clone() const {
  return new Declaration(DataType::clone(this->type), this->name);
}
