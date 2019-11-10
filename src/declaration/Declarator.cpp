#include <DataTypeFactory.h>
#include <Declaration.h>

//
// Constructor
//
Declarator::Declarator(const std::string& name): name(name) {}

//
// Getters
//
const std::string& Declarator::get_name() const {
  return this->name;
}

//
// Build the declaration
//
Declaration* Declarator::build_declaration(DataType* internal_type) const {
  return new Declaration(this->build_data_type(internal_type), this->name);
}
