#include <DataType.h>
#include <Declaration.h>

// Store the state transition diagram

//
// Constructor
//
SpecifierQualifierBuilder::SpecifierQualifierBuilder(): state(SpecifierQualifierState::START) {}

//
// Test state
//
bool SpecifierQualifierBuilder::inside_complex_state() const {
  return this->state == SpecifierQualifierState::COMPLEX_TYPE;
}

bool SpecifierQualifierBuilder::add_void() {
  if (this->inside_complex_state()) { return false; }
  if (this->state != SpecifierQualifierState::START) { return false; }

  this->state          = SpecifierQualifierState::PRIMITIVE;
  this->primitive_type = PrimitiveType::VOID;
  return true;
}

bool SpecifierQualifierBuilder::add_char() {
  if (this->inside_complex_state()) { return false; }
  if (this->state == SpecifierQualifierState::START) {
    this->state          = SpecifierQualifierState::PRIMITIVE;
    this->primitive_type = PrimitiveType::CHAR;
    return true;
  }
}

bool SpecifierQualifierBuilder::add_short() {}

bool SpecifierQualifierBuilder::add_int() {}

bool SpecifierQualifierBuilder::add_long() {}

bool SpecifierQualifierBuilder::add_float() {}

bool SpecifierQualifierBuilder::add_double() {}

bool SpecifierQualifierBuilder::add_signed() {}

bool SpecifierQualifierBuilder::add_unsigned() {}

bool SpecifierQualifierBuilder::add_bool() {}
