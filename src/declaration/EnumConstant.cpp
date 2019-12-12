#include <EnumConstant.h>
#include <Expression.h>
#include <algorithm> /* For std::swap */

//
// Constructor
//
EnumConstant::EnumConstant(const std::string& name, Expression* value): name(name), value(value) {}

//
// Destructor
//
EnumConstant::~EnumConstant() {
  delete (this->value);
}

//
// Copy constructor
//
EnumConstant::EnumConstant(const EnumConstant& other):
  name(other.name), value(Expression::clone(other.value)) {}

//
// Assignment operator
//
EnumConstant& EnumConstant::operator=(const EnumConstant& other) {
  EnumConstant new_enum_constant(other);
  EnumConstant::swap(new_enum_constant, *this);
  return *this;
}

//
// Getters
//
const std::string& EnumConstant::get_name() const {
  return this->name;
}

const Expression* EnumConstant::get_value() const {
  return this->value;
}

//
// Get the next value in the sequence
//
Expression* EnumConstant::get_next_value() const {
  return new AdditionExpression(this->value, new ConstantExpression((C_INT) 1));
}

//
// Swap two enum constants
//
void EnumConstant::swap(EnumConstant& one, EnumConstant& two) {
  std::swap(one.name, two.name);
  std::swap(one.value, two.value);
}
