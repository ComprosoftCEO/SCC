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
bool Declaration::has_name() const {
  return true;
}

const std::string& Declaration::get_name() const {
  return this->name;
}

//
// Downcast to initialzer declaration
//
bool Declaration::has_initializer() const {
  return false;
}

InitDeclaration* Declaration::to_init_declaration() {
  return dynamic_cast<InitDeclaration*>(this);
}

//
// Clone
//
Declaration* Declaration::clone() const {
  return new Declaration(DataType::clone(this->type), this->name);
}
