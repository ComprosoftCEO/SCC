#include <DataType.h>
#include <memory>
#include <utility> /* For std::move */

//
// Constructor
//
Parameter::Parameter(DataType* type): type(type) {}

Parameter::Parameter(DataType* type, const std::string& name): type(type), name(name) {}

//
// Copy constructor and move constructor
//
Parameter::Parameter(const Parameter& other):
  type(other.type ? other.type->clone() : nullptr), name(other.name) {}

Parameter::Parameter(Parameter&& other):
  type(std::exchange(other.type, nullptr)), name(std::move(other.name)) {}

//
// Assignment and moving
//
Parameter& Parameter::operator=(const Parameter& other) {
  std::unique_ptr<DataType> old_type{std::exchange(this->type, nullptr)};

  this->type = other.type ? other.type->clone() : nullptr;
  this->name = other.name;
  return *this;
}

Parameter& Parameter::operator=(Parameter&& other) {
  std::exchange(this->type, other.type);
  std::exchange(this->name, other.name);
  return *this;
}

//
// Destructor
//
Parameter::~Parameter() {
  delete (this->type);
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
