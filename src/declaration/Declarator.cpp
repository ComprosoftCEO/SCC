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
