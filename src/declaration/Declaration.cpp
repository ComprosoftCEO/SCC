#include <DataType.h>
#include <Declaration.h>

//
// Constructor
//
Declaration::Declaration(DataType* type, const std::string& name):
  Declaration(type, name, nullptr) {}

Declaration::Declaration(DataType* type, const std::string& name, Expression* initializer):
  AbstractDeclaration(type), name(name), init(init) {}

//
// Getters
//
const std::string& Declaration::get_name() const {
  return this->name;
}

Expression* Declaration::get_initializer() const {
  return this->init;
}

//
// Clone
//
Declaration* Declaration::clone() const {
  return new Declaration(DataType::clone(this->type), this->name);
}
