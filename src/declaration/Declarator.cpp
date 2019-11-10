#include <DataTypeFactory.h>
#include <Declaration.h>
#include <Expression.h>

//
// Constructor
//
Declarator::Declarator(const std::string& name): Declarator(nullptr, name) {}

Declarator::Declarator(DataTypeFactory* sub_factory, const std::string& name):
  sub_factory(sub_factory), name(name), init(nullptr) {}

//
// Destructor
//
Declarator::~Declarator() {
  delete (this->sub_factory);
  delete (this->init);
}

//
// Getters
//
bool Declarator::has_initializer() const {
  return this->init != nullptr;
}

//
// Modify internal state
//
void Declarator::add_factory(DataTypeFactory* new_factory) {
  new_factory->set_sub_factory(this->sub_factory);
  this->sub_factory = new_factory;
}

void Declarator::set_initializer(Expression* init) {
  delete (this->init);
  this->init = init;
}

//
// Build the declaration
//
Declaration* Declarator::build_declaration(DataType* internal_type) const {
  return new Declaration(this->build_data_type(internal_type), this->name,
                         Expression::clone(this->init));
}

//
// Build the data type
//
DataType* Declarator::build_data_type(DataType* internal_type) const {
  if (this->sub_factory != nullptr) {
    // Tail-end recursion
    this->sub_factory->build_data_type(internal_type);
  }

  return internal_type;
}