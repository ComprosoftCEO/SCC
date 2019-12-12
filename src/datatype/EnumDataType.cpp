#include <DataType.h>
#include <Visitor.h>

static IntDataType SIZE;

//
// Constructor
//
EnumDataType::EnumDataType(const EnumConstantList& values): EnumDataType(values, "") {}

EnumDataType::EnumDataType(const std::string& name):
  DataType(ConcreteDataType::ENUM), incomplete_type(true), name(name) {}

EnumDataType::EnumDataType(const EnumConstantList& values, const std::string& name):
  DataType(ConcreteDataType::ENUM), values(values), name(name) {}

//
// Getters
//
bool EnumDataType::has_name() const {
  return this->name != "";
}

bool EnumDataType::is_anonymous() const {
  return this->has_name();
}

const std::string& EnumDataType::get_name() const {
  return this->name;
}

bool EnumDataType::is_incomplete_type() const {
  return this->incomplete_type;
}

const EnumConstantList& EnumDataType::get_enum_constants() const {
  return this->values;
}

size_t EnumDataType::num_constants() const {
  return this->values.size();
}

//
// Get the underlying data type
//
DataType* EnumDataType::get_underlying_type() const {
  return &SIZE;
}

//
// Update the internal values
//
void EnumDataType::set_enum_constants(const EnumConstantList& values) {
  this->values          = values;
  this->incomplete_type = false;
}

void EnumDataType::set_name(const std::string& name) {
  this->name = name;
}

//
// Get the size of the data type
//
size_t EnumDataType::size() const {
  return this->get_underlying_type()->size();
}

//
// Visit
//
void EnumDataType::visit(DataTypeVisitor& visitor) {
  visitor.accept(*this);
}

//
// Clone
//
EnumDataType* EnumDataType::clone() const {
  if (this->incomplete_type) { return new EnumDataType(this->name); }
  return new EnumDataType(this->values, this->name);
}
