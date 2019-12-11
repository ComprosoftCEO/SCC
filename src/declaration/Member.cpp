#include <DataType.h>
#include <Expression.h>
#include <Member.h>
#include <algorithm> /* For std::swap */

//
// Constructor
//
Member::Member(DataType* type, const std::string& name): Member(type, name, nullptr) {}

Member::Member(DataType* type, const std::string& name, Expression* bitfield):
  type(type), name(name), bitfield(bitfield) {}

Member::Member(DataType* type, Expression* bitfield): Member(type, "", bitfield) {}

//
// Destructor
//
Member::~Member() {
  delete (this->type);
  delete (this->bitfield);
}

//
// Copy constructor
//
Member::Member(const Member& other):
  Member(DataType::clone(other.type), other.name, Expression::clone(other.bitfield)) {}

//
// Assignment operator
//
Member& Member::operator=(const Member& other) {
  Member new_member(other);
  Member::swap(*this, new_member);
  return *this;
}

//
// Getters
//
DataType* Member::get_type() const {
  return this->type;
}

bool Member::has_name() const {
  return this->name != "";
}

const std::string& Member::get_name() const {
  return this->name;
}

bool Member::is_bitfield() const {
  return this->bitfield != nullptr;
}

const Expression* Member::get_bitfield_expression() const {
  return this->bitfield;
}

//
// Swap two members
//
void Member::swap(Member& one, Member& two) {
  std::swap(one.type, two.type);
  std::swap(one.name, two.name);
  std::swap(one.bitfield, two.bitfield);
}
