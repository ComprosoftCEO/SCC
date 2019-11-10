#include <DataType.h>
#include <Declaration.h>
#include <Expression.h>

//
// Constructor
//
Declaration::Declaration(DataType* type, const std::string& name):
  Declaration(type, name, nullptr) {}

Declaration::Declaration(DataType* type, const std::string& name, Expression* init):
  type(type), name(name), init(init) {}

//
// Destructor
//
Declaration::~Declaration() {
  delete (this->type);
  delete (this->init);
}

//
// Getters
//
const std::string& Declaration::get_name() const {
  return this->name;
}

bool Declaration::has_initializer() const {
  return this->init != nullptr;
}

Expression* Declaration::get_initializer() const {
  return this->init;
}
