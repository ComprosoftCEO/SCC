#include <DataType.h>
#include <Declaration.h>
#include <Parameter.h>
#include <algorithm> /* For std::swap */

//
// Constructor
//
Parameter::Parameter(DataType* type): type(type) {}

Parameter::Parameter(DataType* type, const std::string& name): type(type), name(name) {}

Parameter::Parameter(Declaration* decl):
  Parameter(DataType::clone(decl->get_type()), decl->get_name()) {
  delete (decl);
}

//
// Destructor
//
Parameter::~Parameter() {
  delete (this->type);
}

//
// Copy constructor and move constructor
//
Parameter::Parameter(const Parameter& other): type(DataType::clone(other.type)), name(other.name) {}

//
// Assignment and moving
//
Parameter& Parameter::operator=(const Parameter& other) {
  Parameter new_param(other);
  Parameter::swap(*this, new_param);
  return *this;
}

//
// Getters
//
DataType* Parameter::get_type() const {
  return this->type;
}

bool Parameter::has_name() const {
  return this->name != "";
}
const std::string& Parameter::get_name() const {
  return this->name;
}

//
// Swap two parameters
//
void Parameter::swap(Parameter& one, Parameter& two) {
  std::swap(one.type, two.type);
  std::swap(one.name, two.name);
}
